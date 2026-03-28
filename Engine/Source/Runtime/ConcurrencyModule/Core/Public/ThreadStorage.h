#pragma once

#include <unordered_map>
#include <typeindex>
#include "IThread.h"
#include "IConcurrencyFactory.h"
#include "IMutex.h"
#include "ThreadGuard.h"

class ThreadStorage {
public:
    explicit ThreadStorage(IConcurrencyFactory* concurrencyFactory) {
        m_concurrencyFactory = concurrencyFactory;
    }

    void Initialize() {
        m_mutex = m_concurrencyFactory->CreatePlatformMutex(false);
    }

    template<typename TThread> requires(std::is_base_of_v<IThread, TThread>)
    void Store(const TThread* thread) {
        ThreadGuard guard(m_mutex);
        m_threadMap[typeid(TThread)] = thread;
    }

    template<typename TThread> requires(std::is_base_of_v<IThread, TThread>)
    void DeleteFromStorage() {
        ThreadGuard guard(m_mutex);
        m_threadMap.erase(typeid(TThread));
    }

    template<typename TThread> requires(std::is_base_of_v<IThread, TThread>)
    bool TryRetrieve(TThread*& outThread) {
        ThreadGuard guard(m_mutex);
        auto threadIterator = m_threadMap.find(typeid(TThread));
        if (threadIterator == m_threadMap.end())
            return false;

        outThread = static_cast<TThread*>(threadIterator->second);
        return true;
    }

    bool TryRetrieve(uint32_t threadId, IThread*& outThread) const {
        ThreadGuard guard(m_mutex);
        for (const std::pair<const std::type_index, IThread *> &thread: m_threadMap) {
            if (thread.second->GetThreadId() == threadId) {
                outThread = thread.second;
                return true;
            }
        }

        return false;
    }

private:
    std::unordered_map<std::type_index, IThread*> m_threadMap;
    IConcurrencyFactory* m_concurrencyFactory;
    IMutex* m_mutex = nullptr;
};