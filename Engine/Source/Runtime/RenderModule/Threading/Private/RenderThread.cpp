#include "../Public/RenderThread.h"
#include "CommandConsumerThreadContext.h"
#include "DiContainer.h"
#include "ProjectSettings/ProjectSettings.h"
#include "RenderCommand.h"
#include "ThreadSearchService.h"
#include "CommandProcessSystem.h"
#include <cassert>
#include "EngineCoreEventBus.h"
#include "WorldThread.h"
#include "FrameLagConstraintSystem.h"
#include "FrameLagContext.h"
#include "FrameIncrementSystem.h"

void RenderThread::OnThreadBegin() {
    InfiniteThread::OnThreadBegin();
    m_threadProcessor->AddSystem<CommandProcessSystem<RenderCommand>>(m_diContainer->Resolve<ThreadSearchService>());
    m_threadProcessor->AddSystem<FrameLagConstraintSystem<RenderThread, WorldThread>>(m_diContainer->Resolve<ThreadSearchService>(),
        m_diContainer->Resolve<EngineCoreEventBus>());

    m_threadProcessor->AddSystem<FrameIncrementSystem>(m_diContainer->Resolve<EngineCoreEventBus>(), m_diContainer->Resolve<ThreadSearchService>());

    FrameLagContext<WorldThread>* frameLagContext;
    bool retrievedContext = m_threadContext->TryRetrieveContextUnit(frameLagContext);
    assert(retrievedContext);

    frameLagContext->m_frameLagSemaphore->Acquire();
}

void RenderThread::InitializeContext() {
    InfiniteThread::InitializeContext();
    InitializeCommandTreadContext();
    InitializeFrameLagContext();
}

RenderThread::RenderThread(IConcurrencyFactory *concurrencyFactory, ThreadStorage* threadStorage, ProjectSettings* projectSettings,
    DiContainer* diContainer, EngineCoreEventBus* engineCoreEventBus)
: InfiniteThread(concurrencyFactory, threadStorage, engineCoreEventBus), m_projectSettings(projectSettings), m_diContainer(diContainer) { }

void RenderThread::SubmitInfiniteWork() {
    m_engineCoreEventBus->Publish(EngineCoreEvents::EngineBeginFrameEvent(GetThreadId()));

    m_threadProcessor->Tick();

    m_engineCoreEventBus->Publish(EngineCoreEvents::EngineEndFrameEvent(GetThreadId()));
    m_engineCoreEventBus->Publish(EngineCoreEvents::EnginePostEndFrameEvent(GetThreadId()));
}

void RenderThread::InitializeCommandTreadContext() {
    CommandConsumerThreadContext<RenderCommand>* consumerThreadContext =
        m_diContainer->Instantiate<CommandConsumerThreadContext<RenderCommand>>().WithArguments<ThreadSearchService, IConcurrencyFactory>();
    MemoryAllocationSettings memoryAllocationSettings = m_projectSettings->GetMemoryAllocationSettings();
    RenderingSettings renderingSettings = m_projectSettings->GetRenderingSettings();
    consumerThreadContext->Initialize(renderingSettings.m_maxFrameLag, renderingSettings.m_maxFrameLag + 1,
        memoryAllocationSettings.m_commandBufferChunkSize, memoryAllocationSettings.m_maxAllowedMemoryPerCommandBuffer);
    m_threadContext->AddContextUnit(consumerThreadContext);
}

void RenderThread::InitializeFrameLagContext() {
    FrameLagContext<WorldThread>* frameLagContext = m_diContainer->Instantiate<FrameLagContext<WorldThread>>().WithArguments<IConcurrencyFactory>();
    frameLagContext->Initialize(0, m_projectSettings->GetRenderingSettings().m_maxFrameLag);
    m_threadContext->AddContextUnit(frameLagContext);
}