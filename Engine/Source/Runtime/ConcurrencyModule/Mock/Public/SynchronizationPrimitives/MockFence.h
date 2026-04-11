#pragma once

#include "SynchronizationPrimitives/IFence.h"

class MockFence : public IFence {
public:
    void MakeMemoryVisible() override {};
};