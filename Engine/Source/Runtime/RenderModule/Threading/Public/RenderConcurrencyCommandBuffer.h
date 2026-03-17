#pragma once

#include "ConcurrencyCommandBuffer.h"
#include "SynchronizationCommon.h"


template<typename TCommandDelegate>
class RenderConcurrencyCommandBuffer : public ConcurrencyCommandBuffer<TCommandDelegate> {
public:
    void Submit() override {
        //submit to RT render command buffer
        //atomic push to command buffer head
        //atomic retrieve command buffer root
    }
};