#pragma once

#include "InfiniteThread.h"

class ProjectSettings;
class IPlatformInteractor;
class DiContainer;
class RenderCommand;
template<typename TCommand>
class CommandConsumerThreadContext;
class EngineCoreEventBus;
class CommandWriter;
class ThreadSearchService;

class RenderThread : public InfiniteThread {
protected:
    void OnThreadBegin() override;
    void InitializeContext() override;

public:
    RenderThread(IConcurrencyFactory* concurrencyFactory, ThreadStorage* threadStorage, ProjectSettings* projectSettings,
        DiContainer* diContainer, EngineCoreEventBus* engineCoreEventBus, CommandWriter* commandWriter, ThreadSearchService* threadSearchService);
protected:
    void SubmitInfiniteWork() override;

private:
    ProjectSettings* m_projectSettings;
    DiContainer* m_diContainer;
    CommandWriter* m_commandWriter;
    ThreadSearchService* m_threadSearchService;

    void InitializeCommandTreadContext();
    void InitializeFrameLagContext();
};