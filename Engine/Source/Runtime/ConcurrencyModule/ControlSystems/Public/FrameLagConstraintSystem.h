#pragma once

#include "IConcurrencySystem.h"
#include "ThreadSearchService.h"
#include "FrameLagContext.h"
#include "EngineCoreEventBus.h"
#include "ObjectDelegate.h"

template<typename TLocalThread, typename TConstraintThread>
class FrameLagConstraintSystem : public IConcurrencySystem {
public:
    FrameLagConstraintSystem(ThreadSearchService* threadSearchService, EngineCoreEventBus* engineCoreEventBus)
    : m_threadSearchService(threadSearchService), m_engineCoreEventBus(engineCoreEventBus) {
        m_enginePostEndFrameDelegate = new ObjectDelegate<FrameLagConstraintSystem<TLocalThread, TConstraintThread>, const EngineCoreEvents::EnginePostEndFrameEvent&>
                (this, &FrameLagConstraintSystem<TLocalThread, TConstraintThread>::OnEnginePostEndFrame);
    }

    ~FrameLagConstraintSystem() override {
        delete m_enginePostEndFrameDelegate;
    }

    void Start(uint32_t localThreadId) override {
        m_localThreadId = localThreadId;
        m_threadSearchService->TryGetThreadContext(localThreadId, m_localFrameLagContext);

        m_engineCoreEventBus->Subscribe<EngineCoreEvents::EnginePostEndFrameEvent>(m_enginePostEndFrameDelegate);
    }

    void Tick() override { }

    void Terminate() override {
        m_engineCoreEventBus->UnSubscribe<EngineCoreEvents::EnginePostEndFrameEvent>(m_enginePostEndFrameDelegate);
    }

private:
    ThreadSearchService* m_threadSearchService;
    EngineCoreEventBus* m_engineCoreEventBus;
    FrameLagContext<TConstraintThread>* m_localFrameLagContext = nullptr;
    IDelegate<const EngineCoreEvents::EnginePostEndFrameEvent&>* m_enginePostEndFrameDelegate;

    uint32_t m_localThreadId = 0;

    void OnEnginePostEndFrame(const EngineCoreEvents::EnginePostEndFrameEvent& postEndFrameEventData) {
        if (postEndFrameEventData.m_threadId != m_localThreadId)
            return;

        FrameLagContext<TLocalThread>* constraintFrameLagContext;
        if (m_threadSearchService->TryGetThreadContext<TConstraintThread>(constraintFrameLagContext))
            constraintFrameLagContext->m_frameLagSemaphore->Release();

        if (m_localFrameLagContext != nullptr)
            m_localFrameLagContext->m_frameLagSemaphore->Acquire();
    }
};