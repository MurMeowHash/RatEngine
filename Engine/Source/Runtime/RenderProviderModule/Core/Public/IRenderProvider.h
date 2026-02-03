#pragma once

#include <cstdint>

class IRenderProvider {
public:
    virtual void Initialize() = 0;
    [[nodiscard]] virtual uint32_t GetDriverMaxSupportedVersion() const = 0;
    [[nodiscard]] virtual uint32_t GetApiVersion() const = 0;
    virtual ~IRenderProvider() = default;
};