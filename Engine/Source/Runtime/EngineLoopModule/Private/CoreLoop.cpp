#include "../Public/CoreLoop.h"
#include "CoreUtils.h"

Rat::Core::ErrorSeverity CoreLoop::Initialize() {
    m_engineDependencyContext.OpenContext();
    AcquireNeededDependencies();

    m_projectSettingsInitializer->Initialize();

    Rat::Core::ErrorSeverity errorSeverity = Rat::Core::ErrorSeverity::Success;

    errorSeverity = CreateMainWindow();
    if(errorSeverity == Rat::Core::ErrorSeverity::Fatal)
        return errorSeverity;

    m_engineCoreEventBus->Publish(EngineCoreEvents::EngineInitializedEvent());

    return errorSeverity;
}

Rat::Core::ErrorSeverity CoreLoop::Tick() {
    Rat::Core::ErrorSeverity errorSeverity = Rat::Core::ErrorSeverity::Success;



    return errorSeverity;
}

Rat::Core::ErrorSeverity CoreLoop::Exit() {
    Rat::Core::ErrorSeverity errorSeverity = Rat::Core::ErrorSeverity::Success;
    m_windowProvider->Shutdown();
    m_engineDependencyContext.CloseContext();
    return errorSeverity;
}

void CoreLoop::AcquireNeededDependencies() {
    const DiContainer& diContainer = m_engineDependencyContext.GetContainer();
    m_windowProvider = diContainer.Resolve<IWindowProvider>();
    m_engineCoreEventBus = diContainer.Resolve<EngineCoreEventBus>();
    m_projectSettings = diContainer.Resolve<ProjectSettings>();
    m_projectSettingsInitializer = diContainer.Resolve<IProjectSettingsInitializer>();
    m_logger = diContainer.Resolve<ILogger>();
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