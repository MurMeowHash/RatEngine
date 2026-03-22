#include "../Public/RenderableThreadContext.h"
#include "ConcurrencyCommandBufferPool.h"
#include "LinearAllocator.h"
#include "StaticFunc.h"

RenderableThreadContext::RenderableThreadContext(uint32_t bufferPoolSize, uint32_t maxBufferPoolSize, size_t commandBufferChunkSize,
                                                 IAllocator* poolAllocator) {
    m_bufferAllocatorFunc = new StaticFunc<IAllocator*>([commandBufferChunkSize](){
        return new LinearAllocator(commandBufferChunkSize);
    });

    m_commandBufferPool = new ConcurrencyCommandBufferPool<RenderCommand>(bufferPoolSize, maxBufferPoolSize,
                                                                          m_bufferAllocatorFunc, poolAllocator);
}

RenderableThreadContext::~RenderableThreadContext() {
    delete m_commandBufferPool;
    delete m_bufferAllocatorFunc;
}