#include "../Public/RHLLoop.h"
#include "../../Installation/Public/RHLDependencyContext.h"
#include "ILogger.h"
#include "IRHLProviderFactory.h"
#include "RHLRuntimeData.h"
#include "Configurations/RenderApi/RenderApiConfiguration.h"
#include "RenderingApi.h"
#include "PlatformInteractors/IPlatformInteractor.h"
#include "IRHLDependencyContextFactory.h"

RHLLoop::RHLLoop(DiContainer* parentDiContainer, IRHLDependencyContextFactory* rhlDependencyContextFactory,
    ILogger* logger, RHLRuntimeData* rhlRuntimeData, RenderApiConfiguration* renderApiConfiguration,
    IPlatformInteractor* platformInteractor)
: m_parentDiContainer(parentDiContainer), m_rhlDependencyContextFactory(rhlDependencyContextFactory),
m_logger(logger), m_rhlRuntimeData(rhlRuntimeData), m_renderApiConfiguration(renderApiConfiguration),
m_platformInteractor(platformInteractor) { }

RHLLoop::~RHLLoop() {
    delete m_rhlDependencyContext;
}

Rat::Core::ErrorSeverity RHLLoop::Initialize() {
    if (!InitializeRenderingApi())
        return Rat::Core::ErrorSeverity::Fatal;

    m_rhlDependencyContext = m_rhlDependencyContextFactory->CreateRHLDependencyContext(m_rhlRuntimeData->m_usedRenderingApi,
        m_parentDiContainer);
    m_rhlDependencyContext->OpenContext();
    AcquireNeededDependencies();

    Rat::Core::ErrorSeverity errorSeverity = Rat::Core::ErrorSeverity::Success;
    errorSeverity = InitializeRHLProvider();
    return errorSeverity;
}

Rat::Core::ErrorSeverity RHLLoop::Tick() {
    Rat::Core::ErrorSeverity errorSeverity = Rat::Core::ErrorSeverity::Success;
    return errorSeverity;
}

Rat::Core::ErrorSeverity RHLLoop::Exit() {
    Rat::Core::ErrorSeverity errorSeverity = Rat::Core::ErrorSeverity::Success;
    m_rhlRuntimeData->m_rhlProvider->Shutdown();
    delete m_rhlRuntimeData->m_rhlProvider;
    m_rhlDependencyContext->CloseContext();
    return errorSeverity;
}

Rat::Core::ErrorSeverity RHLLoop::InitializeRHLProvider() const {
    bool initialized;
    m_rhlRuntimeData->m_rhlProvider =
        m_rhlProviderFactory->CreateRHLProvider(m_rhlRuntimeData->m_usedRenderingApi, &initialized);

    if (!initialized) {
        m_logger->PrintError(StringFormatter("Failed to initialize render provider with api type ",
            static_cast<uint32_t>(m_rhlRuntimeData->m_usedRenderingApi)));

        return Rat::Core::ErrorSeverity::Fatal;
    }

    return Rat::Core::ErrorSeverity::Success;
}

bool RHLLoop::InitializeRenderingApi() const {
    auto renderApiPriorityConfigurationIterator = m_renderApiConfiguration->m_renderApiPriorityConfigurations.find(m_platformInteractor->GetPlatformRuntimeData().m_platformType);
    if (renderApiPriorityConfigurationIterator == m_renderApiConfiguration->m_renderApiPriorityConfigurations.end()
        || renderApiPriorityConfigurationIterator->second.m_renderApiPriorityQueue.empty())
        return false;

    m_rhlRuntimeData->m_usedRenderingApi = renderApiPriorityConfigurationIterator->second.m_renderApiPriorityQueue[0];
    return m_rhlRuntimeData->m_usedRenderingApi != RenderingApi::None;
}

void RHLLoop::AcquireNeededDependencies() {
    const DiContainer* diContainer = m_rhlDependencyContext->GetContainer();
    m_rhlProviderFactory = diContainer->Resolve<IRHLProviderFactory>();
}