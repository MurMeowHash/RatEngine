#pragma once

#include "InfiniteThread.h"

class ProjectSettings;
class IPlatformInteractor;
class DiContainer;
class RenderCommand;
template<typename TCommand>
class CommandConsumerThreadContext;
class EngineCoreEventBus;
class ILogger;

class RenderThread : public InfiniteThread {
protected:
    void OnThreadBegin() override;
    void InitializeContext() override;

public:
    RenderThread(IConcurrencyFactory* concurrencyFactory, ThreadStorage* threadStorage, ProjectSettings* projectSettings,
        DiContainer* diContainer, EngineCoreEventBus* engineCoreEventBus, ILogger* logger);
protected:
    void SubmitInfiniteWork() override;

private:
    ProjectSettings* m_projectSettings;
    DiContainer* m_diContainer;
    EngineCoreEventBus* m_engineCoreEventBus;
    ILogger* m_logger;

    void InitializeCommandTreadContext();
    void InitializeFrameLagContext();
};