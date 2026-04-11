#pragma once

#include "Event.h"
#include "SynchronizationPrimitives/IMutex.h"
#include "IConcurrencyFactory.h"
#include "SynchronizationPrimitives/ExclusiveThreadGuard.h"
#include "SynchronizationPrimitives/SharedThreadGuard.h"

template<typename...Args>
class ConcurrentEvent : public Event<Args...> {
public:
    explicit ConcurrentEvent(IConcurrencyFactory* concurrencyFactory)
    : m_concurrencyFactory(concurrencyFactory) {
        m_mutex = m_concurrencyFactory->CreatePlatformMutex();
    }

    ~ConcurrentEvent() override {
        m_mutex->Terminate();
        delete m_mutex;
    }

    void Subscribe(IDelegate<Args...>* callback) override {
        ExclusiveThreadGuard guard(m_mutex);
        Event<Args...>::Subscribe(callback);
    }

    void UnSubscribe(IDelegate<Args...>* callback) override {
        ExclusiveThreadGuard guard(m_mutex);
        Event<Args...>::UnSubscribe(callback);
    }

    void Invoke(Args... args) override {
        SharedThreadGuard guard(m_mutex);
        Event<Args...>::Invoke(std::forward<Args>(args)...);
    }

private:
    IConcurrencyFactory* m_concurrencyFactory;

    IMutex* m_mutex;
};