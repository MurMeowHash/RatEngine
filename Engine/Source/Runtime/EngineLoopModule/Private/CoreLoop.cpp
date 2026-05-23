#include <iostream>
#include "../Public/CoreLoop.h"
#include "CoreUtils.h"
#include "IWindowProvider.h"
#include "EngineDependencyContext.h"
#include "EngineCoreEventBus.h"
#include "ProjectSettings/ProjectSettings.h"
#include "ProjectSettings/IProjectSettingsInitializer.h"
#include "ILogger.h"
#include "IRenderProviderInitializer.h"
#include "RenderProviderAccessor.h"
#include "BuildSettings/IBuildSettingsInitializer.h"
#include "Application/IApplicationInitializer.h"
#include "Runner/ThreadRunner.h"
#include "WorldThread.h"
#include "PlatformInteractors/IPlatformInteractor.h"
#include "RenderCommand.h"
#include "RenderThread.h"
#include "CommandWriter.h"
#include "ILogger.h"
#include "ThreadSearchService.h"
#include "IRendererFactory.h"

CoreLoop::CoreLoop() {
    m_engineDependencyContext = new EngineDependencyContext(nullptr);
}

CoreLoop::~CoreLoop() {
    delete m_engineDependencyContext;
}

Rat::Core::ErrorSeverity CoreLoop::Initialize() {
    m_engineDependencyContext->OpenContext();
    AcquireNeededDependencies();

    //TODO: refactor for better initialization
    m_logger->SetOutputStream(&std::cout);
    m_projectSettingsInitializer->Initialize();
    m_buildSettingsInitializer->Initialize();
    m_applicationInitializer->Initialize();

    Rat::Core::ErrorSeverity errorSeverity = Rat::Core::ErrorSeverity::Success;

    InitializeThreads();

    errorSeverity = CreateMainWindow();
    if(errorSeverity == Rat::Core::ErrorSeverity::Fatal)
        return errorSeverity;

    errorSeverity = InitializeRenderProvider();
    if(errorSeverity == Rat::Core::ErrorSeverity::Fatal)
        return errorSeverity;

    m_engineCoreEventBus->Publish(EngineCoreEvents::EngineInitializedEvent());

    return errorSeverity;
}

Rat::Core::ErrorSeverity CoreLoop::Tick() {
    Rat::Core::ErrorSeverity errorSeverity = Rat::Core::ErrorSeverity::Success;

    uint32_t runningThreadId = m_platformInteractor->GetRunningThreadId();
    m_engineCoreEventBus->Publish(EngineCoreEvents::EngineBeginFrameEvent(runningThreadId));

    m_windowProvider->Tick();

    IRendererFactory* rendererFactory = m_rendererFactory;
    m_commandWriter->EnqueueCommand(RenderCommand([rendererFactory]() {
        IRenderer* renderer = rendererFactory->CreateRenderer(RendererType::Forward);
        renderer->Render();
        delete renderer;
    }));

    m_engineCoreEventBus->Publish(EngineCoreEvents::EngineEndFrameEvent(runningThreadId));
    m_engineCoreEventBus->Publish(EngineCoreEvents::EnginePostEndFrameEvent(runningThreadId));
    return errorSeverity;
}

Rat::Core::ErrorSeverity CoreLoop::Exit() {
    Rat::Core::ErrorSeverity errorSeverity = Rat::Core::ErrorSeverity::Success;

    m_threadRunner->StopThreads();
    m_renderProviderAccessor->m_renderProvider->Shutdown();
    m_windowProvider->Shutdown();
    m_engineDependencyContext->CloseContext();
    return errorSeverity;
}

void CoreLoop::AcquireNeededDependencies() {
    const DiContainer* diContainer = m_engineDependencyContext->GetContainer();
    m_windowProvider = diContainer->Resolve<IWindowProvider>();
    m_engineCoreEventBus = diContainer->Resolve<EngineCoreEventBus>();
    m_projectSettings = diContainer->Resolve<ProjectSettings>();
    m_projectSettingsInitializer = diContainer->Resolve<IProjectSettingsInitializer>();
    m_logger = diContainer->Resolve<ILogger>();
    m_renderProviderInitializer = diContainer->Resolve<IRenderProviderInitializer>();
    m_renderProviderAccessor = diContainer->Resolve<RenderProviderAccessor>();
    m_buildSettingsInitializer = diContainer->Resolve<IBuildSettingsInitializer>();
    m_applicationInitializer = diContainer->Resolve<IApplicationInitializer>();
    m_threadRunner = diContainer->Resolve<ThreadRunner>();
    m_platformInteractor = diContainer->Resolve<IPlatformInteractor>();
    m_commandWriter = diContainer->Resolve<CommandWriter>();
    m_threadSearchService = diContainer->Resolve<ThreadSearchService>();
    m_rendererFactory = diContainer->Resolve<IRendererFactory>();
}

Rat::Core::ErrorSeverity CoreLoop::CreateMainWindow() {
    GeneralSettings generalSettings = m_projectSettings->GetGeneralSettings();
    WindowSettings windowSettings = m_projectSettings->GetWindowSettings();

    WindowCreateInfo windowCreateInfo(windowSettings.m_windowWidth,
                                      windowSettings.m_windowHeight,
                                      windowSettings.m_isFullscreen,
                                      generalSettings.m_projectTitle);

    Rat::WindowProviderModule::ExecResult execResult = m_windowProvider->CreateMainWindow(windowCreateInfo);
    if(execResult == Rat::WindowProviderModule::ExecResult::Success)
        return Rat::Core::ErrorSeverity::Success;

    const char* errorDescription = Rat::WindowProviderModule::GetErrorDescription(execResult);

    if(execResult == Rat::WindowProviderModule::ExecResult::WindowAlreadyCreated) {
        m_logger->PrintWarning(StringFormatter("Window creation was aborted: ", errorDescription));
        return Rat::Core::ErrorSeverity::Warning;
    }

    m_logger->PrintError(StringFormatter("Failed to create main window: ", errorDescription));
    return Rat::Core::ErrorSeverity::Fatal;
}

Rat::Core::ErrorSeverity CoreLoop::InitializeRenderProvider() {
    if(!m_renderProviderInitializer->InitializeRenderProvider()) {
        m_logger->PrintError("Failed to create render provider because api is not supported on this platform");
        return Rat::Core::ErrorSeverity::Fatal;
    }

    Rat::RenderProviderModule::ExecResult execResult = m_renderProviderAccessor->m_renderProvider->Initialize();
    const char* errorDescription = Rat::RenderProviderModule::GetErrorDescription(execResult);
    if(execResult == Rat::RenderProviderModule::ExecResult::DebugCreationFailed) {
        m_logger->PrintWarning(StringFormatter("Warning encountered while initializing render provider: ", errorDescription));
        return Rat::Core::ErrorSeverity::Warning;
    }

    if(execResult != Rat::RenderProviderModule::ExecResult::Success) {
        m_logger->PrintError(StringFormatter("Failed to initialize render provider: ", errorDescription));
        return Rat::Core::ErrorSeverity::Fatal;
    }

    return Rat::Core::ErrorSeverity::Success;
}

void CoreLoop::InitializeThreads() {
    m_threadRunner->StartThreadWrapper<WorldThread>()
        .Create<IPlatformInteractor, ThreadStorage, IConcurrencyFactory, EngineCoreEventBus, ProjectSettings, DiContainer>(m_platformInteractor->GetRunningThreadId())
        .AssignCommandAuthority<RenderCommand>();

    RenderThread* renderThread = m_threadRunner->StartThread<RenderThread>()
        .Create<IConcurrencyFactory, ThreadStorage, ProjectSettings, DiContainer, EngineCoreEventBus, CommandWriter, ThreadSearchService>(0, ThreadCreationFlags::Deferred)
        .AssignCommandConsumer<RenderCommand>()
        .RetrieveThread();

    renderThread->Execute();
}
