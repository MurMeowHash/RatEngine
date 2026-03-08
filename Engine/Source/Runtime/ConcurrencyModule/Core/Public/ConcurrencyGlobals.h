#pragma once

#include <cstdint>

namespace Rat::ConcurrencyModule {
    enum class ThreadCreationFlags : uint32_t {
        None = 0,
        Deferred = 1
    };

    enum class ThreadRuntimeFlags : uint64_t {
        None = 0,
        StopRequested = 1,
    };
}