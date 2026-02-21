#include "../../Public/Extensions/VulkanExtensionsAssembler.h"
#include <vulkan/vulkan_raii.hpp>
#include "CoreUtils.h"

VulkanExtensionsAssembler::VulkanExtensionsAssembler(IVulkanPlatformExtensionsProvider *vulkanPlatformExtensionsProvider)
: m_vulkanPlatformExtensionsProvider(vulkanPlatformExtensionsProvider) {}

std::vector<const char *> VulkanExtensionsAssembler::GetRequestedInstanceExtensions(Rat::RenderProviderModule::Vulkan::ExtensionAssembleFlags flags) const {
    std::vector<const char*> requestedInstanceExtensions;
    requestedInstanceExtensions.emplace_back(vk::KHRSurfaceExtensionName);

    if(Rat::Core::Flags::IsFlagSet(flags, Rat::RenderProviderModule::Vulkan::ExtensionAssembleFlags::IncludeDebug))
        requestedInstanceExtensions.emplace_back(vk::EXTDebugUtilsExtensionName);

    std::vector<const char*> platformInstanceExtensions = m_vulkanPlatformExtensionsProvider->GetRequiredInstanceExtensions();
    requestedInstanceExtensions.insert(requestedInstanceExtensions.end(),
                                            std::make_move_iterator(platformInstanceExtensions.begin()),
                                            std::make_move_iterator(platformInstanceExtensions.end()));

    return requestedInstanceExtensions;
}

std::vector<const char *> VulkanExtensionsAssembler::GetAvailableInstanceExtensions(const vk::raii::Context &vulkanContext,
                                                                                    Rat::RenderProviderModule::Vulkan::ExtensionAssembleFlags flags) const {
    std::vector<vk::ExtensionProperties> supportedInstanceExtensions = vulkanContext.enumerateInstanceExtensionProperties();
    std::vector<const char*> requestedInstanceExtensions = GetRequestedInstanceExtensions(flags);
    std::vector<const char*> intersectedExtensions;
    intersectedExtensions.reserve(supportedInstanceExtensions.size());

    for(const char* requestedExtension : requestedInstanceExtensions) {
        auto extensionIterator = std::find_if(supportedInstanceExtensions.begin(), supportedInstanceExtensions.end(),
                                              [requestedExtension](const vk::ExtensionProperties &supportedExtension) {
            return std::strcmp(requestedExtension, supportedExtension.extensionName) == 0;
        });

        if(extensionIterator != supportedInstanceExtensions.end())
            intersectedExtensions.emplace_back(requestedExtension);
    }

    return intersectedExtensions;
}