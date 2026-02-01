#pragma once

#include "IEngineLoop.h"
#include "IWindowProvider.h"
#include "EngineDependencyContext.h"
#include "EngineCoreEventBus.h"
#include "ProjectSettings/ProjectSettings.h"
#include "ProjectSettings/IProjectSettingsInitializer.h"
#include "ILogger.h"

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
    EngineDependencyContext m_engineDependencyContext;

    void AcquireNeededDependencies();
    Rat::Core::ErrorSeverity CreateMainWindow();
};