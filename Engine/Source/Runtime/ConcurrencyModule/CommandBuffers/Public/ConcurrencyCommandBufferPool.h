#pragma once

#include "IConcurrencyCommandBufferPool.h"
#include <cstdint>
#include <queue>
#include "SimpleAllocator.h"
#include "IFunc.h"
#include "StaticFunc.h"

template<typename TCommand>
class ConcurrencyCommandBufferPool : public IConcurrencyCommandBufferPool<TCommand> {
public:
    ConcurrencyCommandBufferPool(uint32_t poolSize, uint32_t maxPoolSize, IAllocator* commandBufferAllocator = nullptr,
                                 IAllocator* allocator = nullptr)
    : m_poolSize(0), m_maxPoolSize(maxPoolSize), m_allocator(allocator), m_usingBufferAllocatorWrapper(true) {
        if(m_allocator == nullptr) {
            m_allocator = new SimpleAllocator(maxPoolSize);
            m_usingBuiltInAllocator = true;
        }

        if (commandBufferAllocator == nullptr) {
            m_usingBuiltInBufferAllocator = true;
            commandBufferAllocator = new SimpleAllocator(0);
        }

        m_bufferAllocatorFunc = new StaticFunc<IAllocator*>([commandBufferAllocator](){ return commandBufferAllocator; });

        AllocatePool(poolSize);
    }

    ConcurrencyCommandBufferPool(uint32_t poolSize, uint32_t maxPoolSize, IFunc<IAllocator*>* bufferAllocatorFunc,
                                 IAllocator* allocator = nullptr)
            : m_poolSize(0), m_maxPoolSize(maxPoolSize), m_allocator(allocator), m_bufferAllocatorFunc(bufferAllocatorFunc),
            m_usingBufferAllocatorWrapper(false) {
        if(m_allocator == nullptr) {
            m_allocator = new SimpleAllocator(maxPoolSize);
            m_usingBuiltInAllocator = true;
        }

        AllocatePool(poolSize);
    }

    void ReturnBufferToPool(ConcurrencyCommandBuffer<TCommand>* commandBuffer) override {
        m_commandBufferPool.push(commandBuffer);
    }

    ConcurrencyCommandBuffer<TCommand>* PopBuffer() override {
        if(m_commandBufferPool.empty()) {
            if(!TryExtendPool())
                return nullptr;
        }

        ConcurrencyCommandBuffer<TCommand>* candidateBuffer = m_commandBufferPool.front();
        m_commandBufferPool.pop();
        return candidateBuffer;
    }

    ~ConcurrencyCommandBufferPool() override {
        if(m_usingBufferAllocatorWrapper) {
            if (m_usingBuiltInBufferAllocator) {
                IAllocator* allocator = m_bufferAllocatorFunc->Invoke();
                allocator->FreeMemory();
                delete allocator;
            }

            delete m_bufferAllocatorFunc;
        }
        else {
            while(!m_commandBufferPool.empty()) {
                ConcurrencyCommandBuffer<TCommand>*& commandBuffer = m_commandBufferPool.front();
                commandBuffer->GetAllocator()->FreeMemory();
                delete commandBuffer->GetAllocator();
                m_commandBufferPool.pop();
            }
        }

        if(m_usingBuiltInAllocator) {
            m_allocator->FreeMemory();
            delete m_allocator;
        }
    }

private:
    uint32_t m_poolSize;
    uint32_t m_maxPoolSize;
    std::queue<ConcurrencyCommandBuffer<TCommand>*> m_commandBufferPool;

    IAllocator* m_allocator;
    IFunc<IAllocator*>* m_bufferAllocatorFunc = nullptr;

    bool m_usingBuiltInAllocator;
    bool m_usingBufferAllocatorWrapper;
    bool m_usingBuiltInBufferAllocator = false;

    bool TryExtendPool() {
        if(m_poolSize >= m_maxPoolSize)
            return false;

        void* allocatedMemory = m_allocator->AllocateMemory(sizeof(ConcurrencyCommandBuffer<TCommand>));
        ConcurrencyCommandBuffer<TCommand>* commandBuffer = new (allocatedMemory) ConcurrencyCommandBuffer<TCommand>(m_bufferAllocatorFunc->Invoke());
        m_commandBufferPool.push(commandBuffer);
        ++m_poolSize;
        return true;
    }

    void AllocatePool(uint32_t poolSize) {
        for(uint32_t i = 0; i < poolSize; i++) {
            TryExtendPool();
        }
    }
};