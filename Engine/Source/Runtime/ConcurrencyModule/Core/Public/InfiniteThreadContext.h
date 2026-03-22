#pragma once

#include <cstdint>
#include "SynchronizationCommon.h"

struct InfiniteThreadContext {
    AtomicSynchronizer<uint64_t> m_threadFrameIndex = AtomicSynchronizer<uint64_t>(0);
};