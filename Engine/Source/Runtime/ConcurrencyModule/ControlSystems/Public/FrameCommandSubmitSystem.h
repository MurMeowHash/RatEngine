#pragma once

#include "CommandProducerThreadContext.h"
#include "CommandConsumerThreadContext.h"
#include "EngineCoreEventBus.h"
#include "ObjectDelegate.h"
#include "InfiniteThreadContext.h"
#include "IConcurrencySystem.h"
#include "ThreadSearchService.h"
#include "CommandThreadStorage.h"

template<typename TCommand>
class FrameCommandSubmitSystem : public IConcurrencySystem {
public:
    FrameCommandSubmitSystem(EngineCoreEventBus* engineCoreEventBus, ThreadSearchService* threadSearchService,
        CommandThreadStorage* commandThreadStorage)
    : m_engineCoreEventBus(engineCoreEventBus), m_threadSearchService(threadSearchService),
    m_commandThreadStorage(commandThreadStorage) {
        m_engineEndFrameDelegate = new ObjectDelegate<FrameCommandSubmitSystem, const EngineCoreEvents::EngineEndFrameEvent&>
        (this, &FrameCommandSubmitSystem::OnEngineEndFrame);
    }

    ~FrameCommandSubmitSystem() override {
        delete m_engineEndFrameDelegate;
    }

    void Start(uint32_t localThreadId) override {
        m_localThreadId = localThreadId;
        m_engineCoreEventBus->Subscribe<EngineCoreEvents::EngineEndFrameEvent>(m_engineEndFrameDelegate);
    }

    void Terminate() override {
        m_engineCoreEventBus->UnSubscribe<EngineCoreEvents::EngineEndFrameEvent>(m_engineEndFrameDelegate);
    }

    void Tick() override { }
private:
    EngineCoreEventBus* m_engineCoreEventBus;
    ThreadSearchService* m_threadSearchService;
    CommandThreadStorage* m_commandThreadStorage;

    uint32_t m_localThreadId = 0;

    IDelegate<const EngineCoreEvents::EngineEndFrameEvent&>* m_engineEndFrameDelegate;

    void OnEngineEndFrame(const EngineCoreEvents::EngineEndFrameEvent& endFrameEventData) {
        if (endFrameEventData.m_threadId != m_localThreadId)
            return;

        uint32_t consumerThreadId = 0;
        if (!m_commandThreadStorage->TryRetrieveCommandConsumer<TCommand>(&consumerThreadId))
            return;

        InfiniteThreadContext* producerInfiniteThreadContext;
        CommandProducerThreadContext<TCommand>* commandProducerThreadContext;
        CommandConsumerThreadContext<TCommand>* commandConsumerThreadContext;

        if (!m_threadSearchService->TryGetThreadContext(m_localThreadId, commandProducerThreadContext)
            || !m_threadSearchService->TryGetThreadContext(consumerThreadId, commandConsumerThreadContext)
            || !m_threadSearchService->TryGetThreadContext(m_localThreadId, producerInfiniteThreadContext))
            return;

        uint64_t commandFrameIndex = producerInfiniteThreadContext->m_threadFrameIndex.RetrieveValue() + commandProducerThreadContext->GetAuthorityFrameOffset();
        commandConsumerThreadContext->EnqueueCommandBuffer(commandFrameIndex, commandProducerThreadContext->m_commandBuffer);
        if (m_commandThreadStorage->HasCommandAuthority<TCommand>(m_localThreadId))
            commandConsumerThreadContext->MarkFrameCompleted(commandFrameIndex);
    }
};