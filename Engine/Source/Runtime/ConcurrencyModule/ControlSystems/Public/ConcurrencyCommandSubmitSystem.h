#pragma once

#include "CommandProducerThreadContext.h"
#include "EngineCoreEventBus.h"
#include "ObjectDelegate.h"
#include "PlatformInteractors/IPlatformInteractor.h"
#include "ThreadStorage.h"
#include "InfiniteThreadContext.h"
#include <cassert>

template<typename TCommand, typename TConsumerThread>
class ConcurrencyCommandSubmitSystem {
public:
    ConcurrencyCommandSubmitSystem(EngineCoreEventBus* engineCoreEventBus, IPlatformInteractor* platformInteractor, ThreadStorage* threadStorage)
    : m_engineCoreEventBus(engineCoreEventBus), m_platformInteractor(platformInteractor), m_threadStorage(threadStorage) {
        m_engineEndFrameDelegate = new ObjectDelegate<ConcurrencyCommandSubmitSystem, const EngineCoreEvents::EngineEndFrameEvent&>
        (this, &ConcurrencyCommandSubmitSystem::OnEngineEndFrame);
    }

    ~ConcurrencyCommandSubmitSystem() {
        delete m_engineEndFrameDelegate;
    }

    void Initialize() const {
        m_engineCoreEventBus->Subscribe<EngineCoreEvents::EngineEndFrameEvent>(m_engineEndFrameDelegate);
    }

    void Dispose() const {
        m_engineCoreEventBus->UnSubscribe<EngineCoreEvents::EngineEndFrameEvent>(m_engineEndFrameDelegate);
    }

private:
    EngineCoreEventBus* m_engineCoreEventBus;
    IPlatformInteractor* m_platformInteractor;
    ThreadStorage* m_threadStorage;
    IDelegate<const EngineCoreEvents::EngineEndFrameEvent&>* m_engineEndFrameDelegate;

    void OnEngineEndFrame(const EngineCoreEvents::EngineEndFrameEvent& endFrameEventData) {
        uint32_t currentThreadId = m_platformInteractor->GetRunningThreadId();
        if (endFrameEventData.m_threadId != currentThreadId)
            return;

        IClientThread* localThread;
        IClientThread* consumerThread;
        bool retrievedAllThreads = TryGetValidatedThread(currentThreadId, localThread) && TryGetValidatedThread<TConsumerThread>(consumerThread);
        assert(retrievedAllThreads);

        InfiniteThreadContext* producerInfiniteThreadContext;
        CommandProducerThreadContext<TCommand>* commandProducerThreadContext;
        CommandConsumerThreadContext<TCommand>* commandConsumerThreadContext;
        bool retrievedAllContexts =
            localThread->GetThreadContext()->TryRetrieveContextUnit(commandProducerThreadContext)
        && localThread->GetThreadContext()->TryRetrieveContextUnit(producerInfiniteThreadContext)
        && consumerThread->GetThreadContext()->TryRetrieveContextUnit(commandConsumerThreadContext);

        assert(retrievedAllContexts);
        uint64_t realFrameIndex = producerInfiniteThreadContext->GetRealFrameIndex();
        commandConsumerThreadContext->EnqueueCommandBuffer(realFrameIndex, commandProducerThreadContext->m_commandBuffer);
        if (commandConsumerThreadContext->HasThreadAuthority())
            commandConsumerThreadContext->MarkFrameCompleted(realFrameIndex);
    }

    [[nodiscard]] bool TryGetValidatedThread(uint32_t threadId, IClientThread*& outThread) const {
        return m_threadStorage->TryRetrieve(threadId, outThread) && !outThread->GetThreadContext()->IsContextBeingDestroyed();
    }

    template<typename TThread>
    [[nodiscard]] bool TryGetValidatedThread(IClientThread*& outThread) const {
        return m_threadStorage->TryRetrieve<TThread>(outThread) && !outThread->GetThreadContext()->IsContextBeingDestroyed();
    }
};