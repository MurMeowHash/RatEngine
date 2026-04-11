#include "../Public/ThreadStorage.h"

ThreadStorage::ThreadStorage(IConcurrencyFactory *concurrencyFactory)
: m_concurrencyFactory(concurrencyFactory) {
    m_mutex = m_concurrencyFactory->CreatePlatformMutex();
    m_onThreadAdded = new ConcurrentEvent<IClientThread*>(concurrencyFactory);
}

ThreadStorage::~ThreadStorage() {
    m_mutex->Terminate();
    delete m_mutex;

    delete m_onThreadAdded;
}

void ThreadStorage::Store(IClientThread *thread) {
    ExclusiveThreadGuard guard(m_mutex);
    m_threadMap[typeid(*thread)] = thread;
    m_onThreadAdded->Invoke(thread);
}

void ThreadStorage::DeleteFromStorage(IClientThread *thread) {
    ExclusiveThreadGuard guard(m_mutex);
    m_threadMap.erase(typeid(*thread));
}

bool ThreadStorage::TryRetrieve(uint32_t threadId, IClientThread *&outThread) const {
    SharedThreadGuard guard(m_mutex);
    for (const std::pair<const std::type_index, IClientThread*> &clientThread: m_threadMap) {
        if (clientThread.second->GetThreadId() == threadId) {
            outThread = clientThread.second;
            return true;
        }
    }

    return false;
}

std::vector<IClientThread *> ThreadStorage::GetAllThreads() const {
    std::vector<IClientThread*> allThreads;
    allThreads.reserve(m_threadMap.size());
    for (const std::pair<const std::type_index, IClientThread *> &threadPair: m_threadMap) {
        allThreads.emplace_back(threadPair.second);
    }

    return allThreads;
}
