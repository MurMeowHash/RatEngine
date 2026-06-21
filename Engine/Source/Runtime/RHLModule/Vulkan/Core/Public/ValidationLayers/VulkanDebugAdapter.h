#pragma once

#include "IVulkanDebugAdapter.h"

class ILogger;

class VulkanDebugAdapter : public IVulkanDebugAdapter {
public:
    explicit VulkanDebugAdapter(ILogger* logger);
    vk::PFN_DebugUtilsMessengerCallbackEXT GetVulkanDebugCallback() override;
private:
    static VKAPI_ATTR vk::Bool32 VKAPI_CALL VulkanDebugCallback(vk::DebugUtilsMessageSeverityFlagBitsEXT severity,
                                                                vk::DebugUtilsMessageTypeFlagsEXT type,
                                                                const vk::DebugUtilsMessengerCallbackDataEXT* pCallbackData, void*);
};