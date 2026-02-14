#pragma once

#include "IEngineLoop.h"

class IWindowProvider;
class EngineCoreEventBus;
class ProjectSettings;
class IProjectSettingsInitializer;
class ILogger;
class EngineDependencyContext;
class IRenderProviderInitializer;
class RenderProviderAccessor;

class CoreLoop : IEngineLoop {
public:
    explicit CoreLoop();
    ~CoreLoop() override;

    Rat::Core::ErrorSeverity Initialize() override;
    Rat::Core::ErrorSeverity Tick() override;
    Rat::Core::ErrorSeverity Exit() override;
private:
    IWindowProvider* m_windowProvider = nullptr;
    EngineCoreEventBus* m_engineCoreEventBus = nullptr;
    ProjectSettings* m_projectSettings = nullptr;
    IProjectSettingsInitializer* m_projectSettingsInitializer = nullptr;
    ILogger* m_logger = nullptr;
    EngineDependencyContext* m_engineDependencyContext = nullptr;
    IRenderProviderInitializer* m_renderProviderInitializer = nullptr;
    RenderProviderAccessor* m_renderProviderAccessor = nullptr;

    void AcquireNeededDependencies();
    Rat::Core::ErrorSeverity CreateMainWindow();
    Rat::Core::ErrorSeverity InitializeRenderProvider();
};