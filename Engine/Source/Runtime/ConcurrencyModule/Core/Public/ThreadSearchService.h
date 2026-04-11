#pragma once

#include <cstdint>
#include "IThreadContextUnit.h"
#include <type_traits>
#include "ThreadStorage.h"
#include "CommandThreadStorage.h"

class ThreadSearchService {
public:
    ThreadSearchService(ThreadStorage* threadStorage, CommandThreadStorage* commandThreadStorage)
    : m_threadStorage(threadStorage), m_commandThreadStorage(commandThreadStorage) {}

    template<typename TThreadContext> requires(std::is_base_of_v<IThreadContextUnit, TThreadContext>)
    [[nodiscard]] bool TryGetThreadContext(uint32_t threadId, TThreadContext*& outThreadContext) {
        IClientThread* thread;
        if (!m_threadStorage->TryRetrieve(threadId, thread) || thread->GetThreadContext()->IsContextBeingDestroyed())
            return false;

        return thread->GetThreadContext()->TryRetrieveContextUnit(outThreadContext);
    }

    template<typename TThread, typename TThreadContext> requires(std::is_base_of_v<IThreadContextUnit, TThreadContext> && std::is_base_of_v<IClientThread, TThread>)
    [[nodiscard]] bool TryGetThreadContext(TThreadContext*& outThreadContext) {
        TThread* thread;
        if (!m_threadStorage->TryRetrieve<TThread>(thread) || thread->GetThreadContext()->IsContextBeingDestroyed())
            return false;

        return thread->GetThreadContext()->TryRetrieveContextUnit(outThreadContext);
    }

    template<typename TCommand, typename TThreadContext> requires(std::is_base_of_v<IThreadContextUnit, TThreadContext>)
    [[nodiscard]] bool TryGetAuthorityThreadContext(TThreadContext*& outThreadContext) {
        uint32_t threadId;
        if (!m_commandThreadStorage->TryRetrieveCommandAuthority<TCommand>(&threadId))
            return false;

        return TryGetThreadContext(threadId, outThreadContext);
    }

    template<typename TCommand, typename TThreadContext> requires(std::is_base_of_v<IThreadContextUnit, TThreadContext>)
    [[nodiscard]] bool TryGetConsumerThreadContext(TThreadContext*& outThreadContext) {
        uint32_t threadId;
        if (!m_commandThreadStorage->TryRetrieveCommandConsumer<TCommand>(&threadId))
            return false;

        return TryGetThreadContext(threadId, outThreadContext);
    }

private:
    ThreadStorage* m_threadStorage;
    CommandThreadStorage* m_commandThreadStorage;
};
