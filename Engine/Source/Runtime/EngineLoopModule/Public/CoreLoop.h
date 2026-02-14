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
    Rat::Core::ErrorSeverity Initialize() override;
    Rat::Core::ErrorSeverity Tick() override;
    Rat::Core::ErrorSeverity Exit() override;
private:
    IWindowProvider* m_windowProvider;
    EngineCoreEventBus* m_engineCoreEventBus;
    ProjectSettings* m_projectSettings;
    IProjectSettingsInitializer* m_projectSettingsInitializer;
    ILogger* m_logger;
    EngineDependencyContext* m_engineDependencyContext;
    IRenderProviderInitializer* m_renderProviderInitializer;
    RenderProviderAccessor* m_renderProviderAccessor;

    void AcquireNeededDependencies();
    Rat::Core::ErrorSeverity CreateMainWindow();
    Rat::Core::ErrorSeverity InitializeRenderProvider();
};