#pragma once

#include "SynchronizationPrimitives/ISemaphore.h"
#include "IConcurrencyFactory.h"
#include "IThreadContextUnit.h"

template<typename TLagThread>
struct FrameLagContext : public IThreadContextUnit {
    FrameLagContext(IConcurrencyFactory* concurrencyFactory)
    : m_concurrencyFactory(concurrencyFactory) { }

    void Initialize(int32_t initialLag, int32_t maxAllowedLag) {
        m_frameLagSemaphore = m_concurrencyFactory->CreatePlatformSemaphore(initialLag, maxAllowedLag);
    }

    ~FrameLagContext() override {
        m_frameLagSemaphore->Terminate();
        delete m_frameLagSemaphore;
    }

    ISemaphore* m_frameLagSemaphore = nullptr;
private:
    IConcurrencyFactory* m_concurrencyFactory;
};