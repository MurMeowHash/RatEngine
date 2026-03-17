#pragma once

#include "IVulkanDeviceProvider.h"

class VulkanDeviceProvider : public IVulkanDeviceProvider {
public:
    [[nodiscard]] bool TryFindVulkanDevice(const vk::raii::Instance &vkInstance, uint64_t predefinedDeviceId,
                                           DeviceSearchFlags flags, vk::raii::PhysicalDevice *physicalDevice) const override;

    [[nodiscard]] uint64_t GetDeviceIdByName(const vk::raii::Instance &vkInstance, const char *physicalDeviceName) const override;
private:
    [[nodiscard]] static uint64_t EncodeDeviceId(uint32_t vendorID, uint32_t deviceID);
    [[nodiscard]] static bool IsGpuType(vk::PhysicalDeviceType physicalDeviceType);
    [[nodiscard]] static bool IsSupportsGraphics(const std::vector<vk::QueueFamilyProperties2> &deviceQueueFamilies);
};