#pragma once

#include <cstdint>
#include "SynchronizationCommon.h"
#include "IThreadContextUnit.h"

struct InfiniteThreadContext : public IThreadContextUnit {
    explicit InfiniteThreadContext(uint64_t authorityFrameIndex)
    : m_threadFrameIndexOffset(authorityFrameIndex) {}

    uint64_t GetRealFrameIndex() {
        return m_threadFrameIndex.RetrieveValue() + m_threadFrameIndexOffset;
    }

    AtomicSynchronizer<uint64_t> m_threadFrameIndex = AtomicSynchronizer<uint64_t>(0);
    uint64_t m_threadFrameIndexOffset = 0;
};