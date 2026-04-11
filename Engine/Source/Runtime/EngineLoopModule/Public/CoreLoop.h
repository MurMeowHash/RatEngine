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
class IBuildSettingsInitializer;
class IApplicationInitializer;
class ThreadRunner;
class IPlatformInteractor;
class CommandWriter;
class ThreadSearchService;

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
    IBuildSettingsInitializer* m_buildSettingsInitializer = nullptr;
    IApplicationInitializer* m_applicationInitializer = nullptr;
    ThreadRunner* m_threadRunner = nullptr;
    IPlatformInteractor* m_platformInteractor = nullptr;
    CommandWriter* m_commandWriter = nullptr;
    ThreadSearchService* m_threadSearchService = nullptr;

    void AcquireNeededDependencies();
    Rat::Core::ErrorSeverity CreateMainWindow();
    Rat::Core::ErrorSeverity InitializeRenderProvider();
    void InitializeThreads();
};