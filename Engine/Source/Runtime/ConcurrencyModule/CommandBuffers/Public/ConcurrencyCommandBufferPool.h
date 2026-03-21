#pragma once

#include "IConcurrencyCommandBufferPool.h"
#include <cstdint>
#include <queue>
#include "LinearAllocator.h"

template<typename TCommand>
class ConcurrencyCommandBufferPool : public IConcurrencyCommandBufferPool<TCommand> {
public:
    ConcurrencyCommandBufferPool(uint32_t poolSize, uint32_t maxPoolSize, IAllocator* allocator = nullptr, IAllocator* commandBufferAllocator = nullptr)
    : m_poolSize(0), m_maxPoolSize(maxPoolSize), m_allocator(allocator), m_commandBufferAllocator(commandBufferAllocator) {
        m_commandBufferPool.reserve(maxPoolSize);

        if(m_allocator == nullptr) {
            m_allocator = new SimpleAllocator(maxPoolSize);
            m_usingBuiltInAllocator = true;
        }

        AllocatePool(poolSize);
    }

    void ReturnBufferToPool(ConcurrencyCommandBuffer<TCommand> *commandBuffer) override {
        m_commandBufferPool.push(commandBuffer);
    }

    ConcurrencyCommandBuffer<TCommand> *PopBuffer() override {
        if(m_commandBufferPool.empty()) {
            if(!TryExtendPool())
                return nullptr;
        }

        ConcurrencyCommandBuffer<TCommand>* candidateBuffer = m_commandBufferPool.front();
        m_commandBufferPool.pop();
        return candidateBuffer;
    }

    ~ConcurrencyCommandBufferPool() {
        if(!m_usingBuiltInAllocator)
            return;

        m_allocator->FreeMemory();
        delete m_allocator;
    }

private:
    uint32_t m_poolSize;
    uint32_t m_maxPoolSize;
    std::queue<ConcurrencyCommandBuffer<TCommand>*> m_commandBufferPool;

    IAllocator* m_allocator;
    IAllocator* m_commandBufferAllocator;
    bool m_usingBuiltInAllocator;

    bool TryExtendPool() {
        if(m_poolSize >= m_maxPoolSize)
            return false;

        void* allocatedMemory = m_allocator->AllocateMemory(sizeof(ConcurrencyCommandBuffer<TCommand>));
        ConcurrencyCommandBuffer<TCommand>* commandBuffer = new (allocatedMemory) ConcurrencyCommandBuffer<TCommand>(m_commandBufferAllocator);
        m_commandBufferPool.push(commandBuffer);
        ++m_poolSize;
        return true;
    }

    void AllocatePool(uint32_t poolSize) {
        for(int i = 0; i < poolSize; i++) {
            TryExtendPool();
        }
    }
};