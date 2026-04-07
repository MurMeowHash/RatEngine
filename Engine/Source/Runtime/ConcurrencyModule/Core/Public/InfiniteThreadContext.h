#pragma once

#include <cstdint>
#include "SynchronizationCommon.h"
#include "IThreadContextUnit.h"

class InfiniteThreadContext : public IThreadContextUnit {
public:
    AtomicSynchronizer<uint64_t> m_threadFrameIndex = AtomicSynchronizer<uint64_t>(0);
};