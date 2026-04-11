#pragma once

#include <cstdint>
#include <map>
#include "IConcurrencyFactory.h"
#include "SynchronizationPrimitives/IMutex.h"
#include "SynchronizationPrimitives/ExclusiveThreadGuard.h"
#include "ConcurrencyCommandBuffer.h"
#include "ConcurrencyCommandBufferPool.h"
#include "StaticFunc.h"
#include "LinearAllocator.h"
#include <stdexcept>
#include <queue>
#include "CommandThreadContextBase.h"

template<typename TCommand>
class CommandConsumerThreadContext : public CommandThreadContextBase<TCommand> {
public:
    explicit CommandConsumerThreadContext(ThreadSearchService* threadSearchService, IConcurrencyFactory* concurrencyFactor)
    : CommandThreadContextBase<TCommand>(threadSearchService), m_concurrencyFactory(concurrencyFactor) { }

    ~CommandConsumerThreadContext() override {
        if (m_frameSlotsMutex != nullptr)
            m_frameSlotsMutex->Terminate();

        delete m_frameSlotsMutex;
        delete m_bufferAllocatorFunc;
        delete m_commandBufferPool;
    }

    void Initialize(uint32_t bufferPoolSize, uint32_t maxBufferPoolSize, size_t commandBufferChunkSize,
        size_t maxAllowedMemoryPerBuffer, IAllocator* poolAllocator = nullptr) {
        CommandThreadContextBase<TCommand>::Initialize();
        m_maxAllowedMemoryPerBuffer = maxAllowedMemoryPerBuffer;

        m_bufferAllocatorFunc = new StaticFunc<IAllocator*>([commandBufferChunkSize](){
            return new LinearAllocator(commandBufferChunkSize);
        });

        m_commandBufferPool = new ConcurrencyCommandBufferPool<TCommand>(bufferPoolSize, maxBufferPoolSize,
            m_bufferAllocatorFunc, poolAllocator);

        m_frameSlotsMutex = m_concurrencyFactory->CreatePlatformMutex();
    }

    void EnqueueCommandBuffer(uint64_t globalFrameIndex, ConcurrencyCommandBuffer<TCommand>* commandBuffer) {
        ExclusiveThreadGuard frameSlotsGuard(m_frameSlotsMutex);
        uint64_t frameIndex = std::max(globalFrameIndex, m_lastCompletedFrameIndex + 1);
        auto cachedCommandBufferIterator = m_bufferFrameSlots.find(frameIndex);
        if (cachedCommandBufferIterator == m_bufferFrameSlots.end()) {
            ConcurrencyCommandBuffer<TCommand>* pooledBuffer = m_commandBufferPool->PopBuffer();
            if (pooledBuffer == nullptr)
                throw std::runtime_error("Unable to pool command buffer, because thread latency is too high");

            auto insertionIterator = m_bufferFrameSlots.emplace(frameIndex, pooledBuffer);
            cachedCommandBufferIterator = insertionIterator.first;
        }

        cachedCommandBufferIterator->second->TransferCommandBuffer(*commandBuffer);
    }

    void MarkFrameCompleted(uint64_t frameIndex) {
        ExclusiveThreadGuard frameSlotsGuard(m_frameSlotsMutex);
        auto commandBufferIterator = m_bufferFrameSlots.find(frameIndex);
        if (commandBufferIterator == m_bufferFrameSlots.end())
            return;

        m_readyToExecuteBuffersQueue.emplace(commandBufferIterator->second);
        m_bufferFrameSlots.erase(commandBufferIterator);
        m_lastCompletedFrameIndex = frameIndex;
    }

    bool TryGetReadyToExecuteBuffer(ConcurrencyCommandBuffer<TCommand>*& outBuffer) {
        ExclusiveThreadGuard frameSlotsGuard(m_frameSlotsMutex);
        if (m_readyToExecuteBuffersQueue.empty())
            return false;

        ConcurrencyCommandBuffer<TCommand>* commandBuffer = m_readyToExecuteBuffersQueue.front();
        m_readyToExecuteBuffersQueue.pop();
        outBuffer = commandBuffer;
        return true;
    }

    void MarkBufferExecuted(ConcurrencyCommandBuffer<TCommand>* commandBuffer) {
        ExclusiveThreadGuard frameSlotsGuard(m_frameSlotsMutex);
        IAllocator* commandBufferAllocator = commandBuffer->GetAllocator();
        if (commandBufferAllocator->GetAllocatedMemorySize() >= m_maxAllowedMemoryPerBuffer)
            commandBufferAllocator->FreeMemory();

        commandBuffer->Clear();
        m_commandBufferPool->ReturnBufferToPool(commandBuffer);
    }

private:
    std::map<uint64_t, ConcurrencyCommandBuffer<TCommand>*> m_bufferFrameSlots;
    std::queue<ConcurrencyCommandBuffer<TCommand>*> m_readyToExecuteBuffersQueue;
    ConcurrencyCommandBufferPool<TCommand>* m_commandBufferPool = nullptr;
    IConcurrencyFactory* m_concurrencyFactory;
    IMutex* m_frameSlotsMutex = nullptr;
    IFunc<IAllocator*>* m_bufferAllocatorFunc = nullptr;

    size_t m_maxAllowedMemoryPerBuffer = 0;
    uint64_t m_lastCompletedFrameIndex = 0;
};
