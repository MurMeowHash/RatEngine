#pragma once

#include <cstdint>
#include "SynchronizationCommon.h"
#include "IThreadContextUnit.h"

struct InfiniteThreadContext : public IThreadContextUnit {
    uint64_t GetRealFrameIndex() {
        return m_threadFrameIndex.RetrieveValue() + m_threadFrameIndexOffset.RetrieveValue();
    }

    AtomicSynchronizer<uint64_t> m_threadFrameIndex = AtomicSynchronizer<uint64_t>(0);
    AtomicSynchronizer<uint64_t> m_threadFrameIndexOffset = AtomicSynchronizer<uint64_t>(0);
};