#include "../Public/FrameIncrementSystem.h"
#include "EngineCoreEventBus.h"
#include "ThreadSearchService.h"
#include "ObjectDelegate.h"
#include "InfiniteThreadContext.h"
#include <cassert>

FrameIncrementSystem::FrameIncrementSystem(EngineCoreEventBus *engineCoreEventBus, ThreadSearchService *threadSearchService)
: m_engineCoreEventBus(engineCoreEventBus), m_threadSearchService(threadSearchService) {
    m_engineBeginFrameDelegate = new ObjectDelegate<FrameIncrementSystem, const EngineCoreEvents::EngineBeginFrameEvent&>
        (this, &FrameIncrementSystem::OnEngineBeginFrame);
}

FrameIncrementSystem::~FrameIncrementSystem() {
    delete m_engineBeginFrameDelegate;
}

void FrameIncrementSystem::Start(uint32_t localThreadId) {
    m_localThreadId = localThreadId;

    bool retrievedThread = m_threadSearchService->TryGetThreadContext(m_localThreadId, m_infiniteThreadContext);
    assert(retrievedThread);

    m_engineCoreEventBus->Subscribe<EngineCoreEvents::EngineBeginFrameEvent>(m_engineBeginFrameDelegate);
}

void FrameIncrementSystem::Tick() { }

void FrameIncrementSystem::Terminate() {
    m_engineCoreEventBus->UnSubscribe<EngineCoreEvents::EngineBeginFrameEvent>(m_engineBeginFrameDelegate);
}

void FrameIncrementSystem::OnEngineBeginFrame(const EngineCoreEvents::EngineBeginFrameEvent &beginFrameEvent) {
    if (beginFrameEvent.m_threadId != m_localThreadId)
        return;

    m_infiniteThreadContext->m_threadFrameIndex.Increment();
}
