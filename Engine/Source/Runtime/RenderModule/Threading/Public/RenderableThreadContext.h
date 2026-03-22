#pragma once

#include "RenderThreadGlobals.h"
#include <cstdint>
#include "IThreadContextUnit.h"

template<typename T>
class IConcurrencyCommandBufferPool;

template<typename TReturn, typename... Args>
class IFunc;

class IAllocator;

struct RenderableThreadContext : public IThreadContextUnit {
    IConcurrencyCommandBufferPool<RenderCommand>* m_commandBufferPool;

    RenderableThreadContext(uint32_t bufferPoolSize, uint32_t maxBufferPoolSize, size_t commandBufferChunkSize, IAllocator* poolAllocator = nullptr);
    ~RenderableThreadContext() override;
private:
    IFunc<IAllocator*>* m_bufferAllocatorFunc;
};