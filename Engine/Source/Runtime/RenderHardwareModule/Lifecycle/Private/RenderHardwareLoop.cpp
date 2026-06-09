#include "../Public/RenderHardwareLoop.h"
#include "../../Installation/Public/RenderHardwareDependencyContext.h"
#include "ILogger.h"
#include "IRenderHardwareProviderFactory.h"
#include "RenderHardwareRuntimeData.h"
#include "Configurations/RenderApi/RenderApiConfiguration.h"
#include "RenderingApi.h"
#include "PlatformInteractors/IPlatformInteractor.h"
#include "IRenderHardwareDependencyContextFactory.h"

RenderHardwareLoop::RenderHardwareLoop(DiContainer* parentDiContainer, IRenderHardwareDependencyContextFactory* renderHardwareDependencyContextFactory,
    ILogger* logger, RenderHardwareRuntimeData* renderHardwareRuntimeData, RenderApiConfiguration* renderApiConfiguration,
    IPlatformInteractor* platformInteractor)
: m_parentDiContainer(parentDiContainer), m_renderHardwareDependencyContextFactory(renderHardwareDependencyContextFactory),
m_logger(logger), m_renderHardwareRuntimeData(renderHardwareRuntimeData), m_renderApiConfiguration(renderApiConfiguration),
m_platformInteractor(platformInteractor) { }

RenderHardwareLoop::~RenderHardwareLoop() {
    delete m_renderHardwareDependencyContext;
}

Rat::Core::ErrorSeverity RenderHardwareLoop::Initialize() {
    if (!InitializeRenderingApi())
        return Rat::Core::ErrorSeverity::Fatal;

    m_renderHardwareDependencyContext = m_renderHardwareDependencyContextFactory->CreateRenderHardwareDependencyContext(m_renderHardwareRuntimeData->m_usedRenderingApi,
        m_parentDiContainer);
    m_renderHardwareDependencyContext->OpenContext();
    AcquireNeededDependencies();

    Rat::Core::ErrorSeverity errorSeverity = Rat::Core::ErrorSeverity::Success;
    errorSeverity = InitializeRenderHardwareProvider();
    return errorSeverity;
}

Rat::Core::ErrorSeverity RenderHardwareLoop::Tick() {
    Rat::Core::ErrorSeverity errorSeverity = Rat::Core::ErrorSeverity::Success;
    return errorSeverity;
}

Rat::Core::ErrorSeverity RenderHardwareLoop::Exit() {
    Rat::Core::ErrorSeverity errorSeverity = Rat::Core::ErrorSeverity::Success;
    m_renderHardwareRuntimeData->m_renderHardwareProvider->Shutdown();
    delete m_renderHardwareRuntimeData->m_renderHardwareProvider;
    m_renderHardwareDependencyContext->CloseContext();
    return errorSeverity;
}

Rat::Core::ErrorSeverity RenderHardwareLoop::InitializeRenderHardwareProvider() const {
    bool initialized;
    m_renderHardwareRuntimeData->m_renderHardwareProvider =
        m_renderHardwareProviderFactory->CreateRenderHardwareProvider(m_renderHardwareRuntimeData->m_usedRenderingApi, &initialized);

    if (!initialized) {
        m_logger->PrintError(StringFormatter("Failed to initialize render provider with api type ",
            static_cast<uint32_t>(m_renderHardwareRuntimeData->m_usedRenderingApi)));

        return Rat::Core::ErrorSeverity::Fatal;
    }

    return Rat::Core::ErrorSeverity::Success;
}

bool RenderHardwareLoop::InitializeRenderingApi() const {
    auto renderApiPriorityConfigurationIterator = m_renderApiConfiguration->m_renderApiPriorityConfigurations.find(m_platformInteractor->GetPlatformRuntimeData().m_platformType);
    if (renderApiPriorityConfigurationIterator == m_renderApiConfiguration->m_renderApiPriorityConfigurations.end()
        || renderApiPriorityConfigurationIterator->second.m_renderApiPriorityQueue.empty())
        return false;

    m_renderHardwareRuntimeData->m_usedRenderingApi = renderApiPriorityConfigurationIterator->second.m_renderApiPriorityQueue[0];
    return m_renderHardwareRuntimeData->m_usedRenderingApi != RenderingApi::None;
}

void RenderHardwareLoop::AcquireNeededDependencies() {
    const DiContainer* diContainer = m_renderHardwareDependencyContext->GetContainer();
    m_renderHardwareProviderFactory = diContainer->Resolve<IRenderHardwareProviderFactory>();
}