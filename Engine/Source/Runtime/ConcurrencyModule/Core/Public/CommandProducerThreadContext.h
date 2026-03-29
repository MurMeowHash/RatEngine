#pragma once

#include "IThreadContextUnit.h"
#include "ConcurrencyCommandBuffer.h"
#include "IAllocator.h"
#include "SimpleAllocator.h"

template<typename TCommand>
struct CommandProducerThreadContext : public IThreadContextUnit {
    CommandProducerThreadContext(IAllocator* commandBufferAllocator = nullptr)
    : m_commandBufferAllocator(commandBufferAllocator) {
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

    ConcurrencyCommandBuffer<TCommand>* m_commandBuffer;
private:
    IAllocator* m_commandBufferAllocator;
    bool m_usingBuiltInAllocator;
};