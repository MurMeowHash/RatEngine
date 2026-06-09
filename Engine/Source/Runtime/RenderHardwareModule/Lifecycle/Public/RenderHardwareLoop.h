#pragma once

#include "IEngineLoop.h"

class RenderHardwareDependencyContext;
class DiContainer;
class ILogger;
struct RenderHardwareRuntimeData;
struct RenderApiConfiguration;
enum class RenderingApi;
class IPlatformInteractor;
class IRenderHardwareProviderFactory;
class IRenderHardwareDependencyContextFactory;

class RenderHardwareLoop : public IEngineLoop {
public:
    RenderHardwareLoop(DiContainer* parentDiContainer, IRenderHardwareDependencyContextFactory* renderHardwareDependencyContextFactory,
        ILogger* logger, RenderHardwareRuntimeData* renderHardwareRuntimeData, RenderApiConfiguration* renderApiConfiguration,
        IPlatformInteractor* platformInteractor);
    ~RenderHardwareLoop() override;

    Rat::Core::ErrorSeverity Initialize() override;
    Rat::Core::ErrorSeverity Tick() override;
    Rat::Core::ErrorSeverity Exit() override;

private:
    RenderHardwareDependencyContext* m_renderHardwareDependencyContext = nullptr;

    DiContainer* m_parentDiContainer;
    IRenderHardwareDependencyContextFactory* m_renderHardwareDependencyContextFactory;
    ILogger* m_logger;
    RenderHardwareRuntimeData* m_renderHardwareRuntimeData;
    RenderApiConfiguration* m_renderApiConfiguration;
    IPlatformInteractor* m_platformInteractor;

    IRenderHardwareProviderFactory* m_renderHardwareProviderFactory = nullptr;

    Rat::Core::ErrorSeverity InitializeRenderHardwareProvider() const;
    [[nodiscard]] bool InitializeRenderingApi() const;

    void AcquireNeededDependencies();
};
