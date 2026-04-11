#pragma once

#include <unordered_map>
#include <typeindex>
#include "SynchronizationPrimitives/IMutex.h"
#include "IConcurrencyFactory.h"
#include "SynchronizationPrimitives/ExclusiveThreadGuard.h"
#include "SynchronizationPrimitives/SharedThreadGuard.h"

class CommandThreadStorage {
public:
    explicit CommandThreadStorage(IConcurrencyFactory* concurrencyFactory)
    : m_concurrencyFactory(concurrencyFactory) {
        m_authorityMutex = m_concurrencyFactory->CreatePlatformMutex();
        m_consumerMutex = m_concurrencyFactory->CreatePlatformMutex();
    }

    ~CommandThreadStorage() {
        m_authorityMutex->Terminate();
        m_consumerMutex->Terminate();
        delete m_authorityMutex;
        delete m_consumerMutex;
    }

    template<typename TCommand>
    void AssignCommandAuthority(uint32_t authorityThreadId) {
        ExclusiveThreadGuard guard(m_authorityMutex);
        m_commandAuthorityThreadMap[typeid(TCommand)] = authorityThreadId;
    }

    template<typename TCommand>
    [[nodiscard]] bool HasCommandAuthority(uint32_t threadId) {
        uint32_t authorityThreadId;
        if (!TryRetrieveCommandAuthority<TCommand>(&authorityThreadId))
            return false;

        return threadId == authorityThreadId;
    }

    template<typename TCommand>
    [[nodiscard]] bool TryRetrieveCommandAuthority(uint32_t* authorityThreadId) {
        SharedThreadGuard guard(m_authorityMutex);
        auto commandAuthorityIterator = m_commandAuthorityThreadMap.find(typeid(TCommand));
        if (commandAuthorityIterator == m_commandAuthorityThreadMap.end())
            return false;

        *authorityThreadId = commandAuthorityIterator->second;
        return true;
    }

    template<typename TCommand>
    void RemoveAuthorityMapping() {
        ExclusiveThreadGuard guard(m_authorityMutex);
        m_commandAuthorityThreadMap.erase(typeid(TCommand));
    }

    template<typename TCommand>
    void SetCommandConsumer(uint32_t threadId) {
        ExclusiveThreadGuard guard(m_consumerMutex);
        m_commandConsumerThreadMap[typeid(TCommand)] = threadId;
    }

    template<typename TCommand>
    void RemoveCommandConsumer() {
        ExclusiveThreadGuard guard(m_consumerMutex);
        m_commandConsumerThreadMap.erase(typeid(TCommand));
    }

    template<typename TCommand>
    [[nodiscard]] bool TryRetrieveCommandConsumer(uint32_t* consumerThreadId) {
        SharedThreadGuard guard(m_consumerMutex);
        auto commandConsumerIterator = m_commandConsumerThreadMap.find(typeid(TCommand));
        if (commandConsumerIterator == m_commandConsumerThreadMap.end())
            return false;

        *consumerThreadId = commandConsumerIterator->second;
        return true;
    }

private:
    IConcurrencyFactory* m_concurrencyFactory;

    std::unordered_map<std::type_index, uint32_t> m_commandAuthorityThreadMap;
    std::unordered_map<std::type_index, uint32_t> m_commandConsumerThreadMap;
    IMutex* m_authorityMutex;
    IMutex* m_consumerMutex;
};