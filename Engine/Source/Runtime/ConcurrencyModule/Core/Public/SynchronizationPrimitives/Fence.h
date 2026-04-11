#pragma once

#include "IConcurrencyFactory.h"

class Fence {
public:
    explicit Fence(IConcurrencyFactory* concurrencyFactory)
    : m_concurrencyFactory(concurrencyFactory) {
        m_fence = m_concurrencyFactory->CreatePlatformFence(true);
    }

    ~Fence() {
        delete m_fence;
    }

private:
    IConcurrencyFactory* m_concurrencyFactory;
    IFence* m_fence;
};