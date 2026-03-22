#pragma once

#include <cstdint>
#include "SynchronizationCommon.h"
#include "IThreadContextUnit.h"

struct InfiniteThreadContext : public IThreadContextUnit {
    AtomicSynchronizer<uint64_t> m_threadFrameIndex = AtomicSynchronizer<uint64_t>(0);
};