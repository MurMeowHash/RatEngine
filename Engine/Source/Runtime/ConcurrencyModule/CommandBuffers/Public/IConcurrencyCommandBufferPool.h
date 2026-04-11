#pragma once

#include "ConcurrencyCommandBuffer.h"

template<typename TCommand>
class IConcurrencyCommandBufferPool {
public:
    virtual void ReturnBufferToPool(ConcurrencyCommandBuffer<TCommand>* commandBuffer) = 0;
    [[nodiscard]] virtual ConcurrencyCommandBuffer<TCommand>* PopBuffer() = 0;
    virtual ~IConcurrencyCommandBufferPool() = default;
};