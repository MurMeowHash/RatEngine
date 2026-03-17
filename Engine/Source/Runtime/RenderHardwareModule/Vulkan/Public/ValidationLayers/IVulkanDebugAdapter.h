#pragma once

#include <functional>
#include <vulkan/vulkan_raii.hpp>

class IVulkanDebugAdapter {
public:
    virtual vk::PFN_DebugUtilsMessengerCallbackEXT GetVulkanDebugCallback() = 0;
    virtual ~IVulkanDebugAdapter() = default;
};