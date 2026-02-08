#include "ValidationLayers/VulkanDebugAdapter.h"
#include "ILogger.h"
#include "CoreUtils.h"

ILogger *g_logger;

VulkanDebugAdapter::VulkanDebugAdapter(ILogger *logger) {
    g_logger = logger;
}

vk::PFN_DebugUtilsMessengerCallbackEXT VulkanDebugAdapter::GetVulkanDebugCallback() {
    return VulkanDebugCallback;
}

vk::Bool32 VKAPI_CALL VulkanDebugAdapter::VulkanDebugCallback(vk::DebugUtilsMessageSeverityFlagBitsEXT severity,
                                                              vk::DebugUtilsMessageTypeFlagsEXT type,
                                                              const vk::DebugUtilsMessengerCallbackDataEXT *pCallbackData,
                                                              void *) {
    std::string typeStr = (type & vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation) ? "Validation" :
                          (type & vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance) ? "Performance" : "General";

    std::string message = StringFormatter(
            "Vulkan ", typeStr, " [",
            pCallbackData->pMessageIdName ? pCallbackData->pMessageIdName : "Unknown",
            "]: ",
            pCallbackData->pMessage ? pCallbackData->pMessage : "No message provided"
    );

    if (severity >= vk::DebugUtilsMessageSeverityFlagBitsEXT::eError) {
        g_logger->PrintError(message);
    } else if (severity >= vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning) {
        g_logger->PrintWarning(message);
    } else {
        g_logger->PrintInfo(message);
    }

    return VK_FALSE;
}
