#pragma once

#include <unordered_map>
#include <typeindex>
#include "IClientThread.h"
#include "IConcurrencyFactory.h"
#include "SynchronizationPrimitives/IMutex.h"
#include "SynchronizationPrimitives/SharedThreadGuard.h"
#include "SynchronizationPrimitives/ExclusiveThreadGuard.h"

class ThreadStorage {
public:
    explicit ThreadStorage(IConcurrencyFactory* concurrencyFactory)
    : m_concurrencyFactory(concurrencyFactory) {
        m_mutex = m_concurrencyFactory->CreatePlatformMutex();
    }

    ~ThreadStorage() {
        m_mutex->Terminate();
        delete m_mutex;
    }

    template<typename TThread> requires(std::is_base_of_v<IClientThread, TThread>)
    void Store(TThread* thread) {
        ExclusiveThreadGuard guard(m_mutex);
        m_threadMap[typeid(TThread)] = thread;
    }

    template<typename TThread> requires(std::is_base_of_v<IClientThread, TThread>)
    void DeleteFromStorage() {
        ExclusiveThreadGuard guard(m_mutex);
        m_threadMap.erase(typeid(TThread));
    }

    void DeleteFromStorage(IClientThread* thread) {
        ExclusiveThreadGuard guard(m_mutex);
        m_threadMap.erase(typeid(*thread));
    }

    template<typename TThread> requires(std::is_base_of_v<IClientThread, TThread>)
    bool TryRetrieve(TThread*& outThread) {
        SharedThreadGuard guard(m_mutex);
        auto threadIterator = m_threadMap.find(typeid(TThread));
        if (threadIterator == m_threadMap.end())
            return false;

        outThread = static_cast<TThread*>(threadIterator->second);
        return true;
    }

    bool TryRetrieve(uint32_t threadId, IClientThread*& outThread) const {
        SharedThreadGuard guard(m_mutex);
        for (const std::pair<const std::type_index, IClientThread*> &clientThread: m_threadMap) {
            if (clientThread.second->GetThreadId() == threadId) {
                outThread = clientThread.second;
                return true;
            }
        }

        return false;
    }

private:
    std::unordered_map<std::type_index, IClientThread*> m_threadMap;
    IConcurrencyFactory* m_concurrencyFactory;
    IMutex* m_mutex = nullptr;
};