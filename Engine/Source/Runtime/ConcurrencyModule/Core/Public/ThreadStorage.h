#pragma once

#include <unordered_map>
#include <typeindex>
#include "IClientThread.h"
#include "IConcurrencyFactory.h"
#include "SynchronizationPrimitives/IMutex.h"
#include "SynchronizationPrimitives/SharedThreadGuard.h"
#include "SynchronizationPrimitives/ExclusiveThreadGuard.h"
#include "ConcurrentEvent.h"
#include <vector>

class ThreadStorage {
public:
    ConcurrentEvent<IClientThread*>* m_onThreadAdded = nullptr;

    explicit ThreadStorage(IConcurrencyFactory* concurrencyFactory);

    ~ThreadStorage();

    void Store(IClientThread* thread);

    template<typename TThread> requires(std::is_base_of_v<IClientThread, TThread>)
    void DeleteFromStorage() {
        ExclusiveThreadGuard guard(m_mutex);
        m_threadMap.erase(typeid(TThread));
    }

    void DeleteFromStorage(IClientThread* thread);

    template<typename TThread> requires(std::is_base_of_v<IClientThread, TThread>)
    bool TryRetrieve(TThread*& outThread) {
        SharedThreadGuard guard(m_mutex);
        auto threadIterator = m_threadMap.find(typeid(TThread));
        if (threadIterator == m_threadMap.end())
            return false;

        outThread = static_cast<TThread*>(threadIterator->second);
        return true;
    }

    bool TryRetrieve(uint32_t threadId, IClientThread*& outThread) const;

    std::vector<IClientThread*> GetAllThreads() const;

private:
    std::unordered_map<std::type_index, IClientThread*> m_threadMap;
    IConcurrencyFactory* m_concurrencyFactory;
    IMutex* m_mutex = nullptr;
};