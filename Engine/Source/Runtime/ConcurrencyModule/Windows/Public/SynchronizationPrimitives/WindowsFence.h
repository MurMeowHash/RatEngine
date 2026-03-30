#pragma once

#include "SynchronizationPrimitives/IFence.h"

class WindowsFence : public IFence {
public:
    explicit WindowsFence(bool invokeMemoryBarrier);
    void MakeMemoryVisible() override;
};