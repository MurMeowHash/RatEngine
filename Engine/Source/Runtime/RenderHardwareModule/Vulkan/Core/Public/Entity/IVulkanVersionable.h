#pragma once

#include <cstdint>

class IVulkanVersionable {
public:
    virtual void SetApiVersion(uint32_t apiVersion) = 0;
    [[nodiscard]] virtual uint32_t GetApiVersion() const = 0;
    virtual ~IVulkanVersionable() = default;
};