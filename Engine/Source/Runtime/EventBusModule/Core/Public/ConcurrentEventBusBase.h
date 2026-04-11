#pragma once

#include "EventBusBase.h"
#include "IConcurrencyFactory.h"
#include "SynchronizationPrimitives/IMutex.h"
#include "SynchronizationPrimitives/ExclusiveThreadGuard.h"
#include "SynchronizationPrimitives/SharedThreadGuard.h"

template<typename TEventBase>
class ConcurrentEventBusBase {
public:
    explicit ConcurrentEventBusBase(IConcurrencyFactory* concurrencyFactory)
    : m_concurrencyFactory(concurrencyFactory) {
        m_mutex = m_concurrencyFactory->CreatePlatformMutex();
        m_internalEventBus = new EventBusBase<TEventBase>();
    }

    ~ConcurrentEventBusBase() {
        m_mutex->Terminate();
        delete m_mutex;
        delete m_internalEventBus;
    }

    template<typename TEvent> requires(std::is_base_of_v<TEventBase, TEvent>)
    void Publish(const TEvent& event) const {
        std::vector<StaticDelegate<const TEventBase&>> snapshot;
        {
            SharedThreadGuard guard(m_mutex);
            snapshot = m_internalEventBus->template GetListenersSnapshot<TEvent>();
        }

        for (const StaticDelegate<const TEventBase&>& eventHandler : snapshot) {
            eventHandler(event);
        }
    }

    template<typename TEvent> requires(std::is_base_of_v<TEventBase, TEvent>)
    void Subscribe(IDelegate<const TEvent&>* eventHandler) {
        ExclusiveThreadGuard guard(m_mutex);
        m_internalEventBus->Subscribe(eventHandler);
    }

    template<typename TEvent> requires(std::is_base_of_v<TEventBase, TEvent>)
    void UnSubscribe(IDelegate<const TEvent &>* eventHandler) {
        ExclusiveThreadGuard guard(m_mutex);
        m_internalEventBus->UnSubscribe(eventHandler);
    }

private:
    IConcurrencyFactory* m_concurrencyFactory;
    IMutex* m_mutex = nullptr;
    EventBusBase<TEventBase>* m_internalEventBus = nullptr;
};