#pragma once

#include "IEngineLoop.h"

class RHLDependencyContext;
class DiContainer;
class ILogger;
struct RHLRuntimeData;
struct RenderApiConfiguration;
enum class RenderingApi;
class IPlatformInteractor;
class IRHLProviderFactory;
class IRHLDependencyContextFactory;

class RHLLoop : public IEngineLoop {
public:
    RHLLoop(DiContainer* parentDiContainer, IRHLDependencyContextFactory* rhlDependencyContextFactory,
        ILogger* logger, RHLRuntimeData* rhlRuntimeData, RenderApiConfiguration* renderApiConfiguration,
        IPlatformInteractor* platformInteractor);
    ~RHLLoop() override;

    Rat::Core::ErrorSeverity Initialize() override;
    Rat::Core::ErrorSeverity Tick() override;
    Rat::Core::ErrorSeverity Exit() override;

private:
    RHLDependencyContext* m_rhlDependencyContext = nullptr;

    DiContainer* m_parentDiContainer;
    IRHLDependencyContextFactory* m_rhlDependencyContextFactory;
    ILogger* m_logger;
    RHLRuntimeData* m_rhlRuntimeData;
    RenderApiConfiguration* m_renderApiConfiguration;
    IPlatformInteractor* m_platformInteractor;

    IRHLProviderFactory* m_rhlProviderFactory = nullptr;

    Rat::Core::ErrorSeverity InitializeRHLProvider() const;
    [[nodiscard]] bool InitializeRenderingApi() const;

    void AcquireNeededDependencies();
};
