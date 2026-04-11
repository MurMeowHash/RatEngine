#pragma once

#include "ConcurrencyCommandBuffer.h"
#include "IAllocator.h"
#include "SimpleAllocator.h"
#include "CommandThreadContextBase.h"

template<typename TCommand>
struct CommandProducerThreadContext : public CommandThreadContextBase<TCommand> {
    explicit CommandProducerThreadContext(ThreadSearchService* threadSearchService)
    : CommandThreadContextBase<TCommand>(threadSearchService) {}

    void Initialize(IAllocator* commandBufferAllocator = nullptr) {
        CommandThreadContextBase<TCommand>::Initialize();
        m_commandBufferAllocator = commandBufferAllocator;
        if (m_commandBufferAllocator == nullptr) {
            m_usingBuiltInAllocator = true;
            m_commandBufferAllocator = new SimpleAllocator(0);
        }

        m_commandBuffer = new ConcurrencyCommandBuffer<TCommand>(m_commandBufferAllocator);
    }

    ~CommandProducerThreadContext() override {
        delete m_commandBuffer;
        if (m_usingBuiltInAllocator) {
            m_commandBufferAllocator->FreeMemory();
            delete m_commandBufferAllocator;
        }
    }

    ConcurrencyCommandBuffer<TCommand>* m_commandBuffer = nullptr;
private:
    IAllocator* m_commandBufferAllocator = nullptr;
    bool m_usingBuiltInAllocator = false;
};