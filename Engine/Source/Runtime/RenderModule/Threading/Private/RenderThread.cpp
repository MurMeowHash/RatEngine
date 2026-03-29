#include "../Public/RenderThread.h"
#include "ObjectDelegate.h"
#include "CommandConsumerThreadContext.h"
#include "RenderThreadGlobals.h"
#include "ProjectSettings/ProjectSettings.h"
#include "ConcurrencyCommandSubmitSystem.h"

void RenderThread::InitializeContext() {
    InfiniteThread::InitializeContext();
    InitializeCommandTreadContext();
}

RenderThread::RenderThread(IConcurrencyFactory *platformThreadFactory, ThreadStorage* threadStorage,
    ProjectSettings* projectSettings, IPlatformInteractor* platformInteractor)
: InfiniteThread(platformThreadFactory, threadStorage), m_projectSettings(projectSettings), m_platformInteractor(platformInteractor) { }

void RenderThread::SubmitInfiniteWork() {

}

void RenderThread::InitializeCommandTreadContext() {
    CommandConsumerThreadContext<RenderCommand>* commandThreadContext = new CommandConsumerThreadContext<RenderCommand>(m_concurrencyFactory, m_platformInteractor);
    MemoryAllocationSettings memoryAllocationSettings = m_projectSettings->GetMemoryAllocationSettings();
    RenderingSettings renderingSettings = m_projectSettings->GetRenderingSettings();
    commandThreadContext->Initialize(renderingSettings.m_maxFramesInFlight, renderingSettings.m_maxFramesInFlight + 1,
        memoryAllocationSettings.m_commandBufferChunkSize, memoryAllocationSettings.m_maxAllowedMemoryPerCommandBuffer);
    m_threadContext->AddContextUnit(commandThreadContext);
}