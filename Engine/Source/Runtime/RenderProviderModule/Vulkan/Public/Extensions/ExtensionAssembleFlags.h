#pragma once

#include <type_traits>
#include <cstdint>

namespace Rat::RenderProviderModule::Vulkan {
    enum class ExtensionAssembleFlags : uint32_t {
        None = 0,
        IncludeDebug = 1u << 0
    };

    inline ExtensionAssembleFlags operator|(ExtensionAssembleFlags a, ExtensionAssembleFlags b) {
        using T = std::underlying_type_t<ExtensionAssembleFlags>;
        return static_cast<ExtensionAssembleFlags>(static_cast<T>(a) | static_cast<T>(b));
    }

    inline ExtensionAssembleFlags operator&(ExtensionAssembleFlags a, ExtensionAssembleFlags b) {
        using T = std::underlying_type_t<ExtensionAssembleFlags>;
        return static_cast<ExtensionAssembleFlags>(static_cast<T>(a) & static_cast<T>(b));
    }

    inline ExtensionAssembleFlags& operator|=(ExtensionAssembleFlags& a, ExtensionAssembleFlags b) {
        a = a | b;
        return a;
    }

    inline bool IsFlagSet(ExtensionAssembleFlags value, ExtensionAssembleFlags flag) {
        using T = std::underlying_type_t<ExtensionAssembleFlags>;
        return (static_cast<T>(value) & static_cast<T>(flag)) != 0;
    }
}