#pragma once

#include <cstdint>

namespace Rat::RenderProviderModule::Vulkan {
    enum class ExtensionAssembleFlags : uint32_t {
        None = 0,
        IncludeDebug = 1u << 0
    };

    enum class DeviceSearchFlags : uint32_t {
        None = 0,
        AllowNonGpu = 1u << 0,
        RenderingOnly = 1u << 1,
    };
}