#include "../../Public/Extensions/VulkanExtensionsValidator.h"

void VulkanExtensionsValidator::ValidateInstanceExtensions(const vk::raii::Context& context,
    std::vector<VulkanExtension> &requestedExtension) {
    vk::ResultValue<std::vector<vk::ExtensionProperties>> supportedInstanceExtensions = context.enumerateInstanceExtensionProperties();
    if (supportedInstanceExtensions.result != vk::Result::eSuccess)
        return;

    FilterExtensions(requestedExtension, supportedInstanceExtensions.value);
}

void VulkanExtensionsValidator::ValidateDeviceExtensions(const vk::raii::PhysicalDevice& physicalDevice,
    std::vector<VulkanExtension> &requestedExtension) {
    vk::ResultValue<std::vector<vk::ExtensionProperties>> supportedDeviceExtensions = physicalDevice.enumerateDeviceExtensionProperties();
    if (supportedDeviceExtensions.result != vk::Result::eSuccess)
        return;

    FilterExtensions(requestedExtension, supportedDeviceExtensions.value);
}

void VulkanExtensionsValidator::ValidateExtensions(IVulkanExtensible *vulkanExtensible,
    std::vector<VulkanExtension> &requestedExtension) {
    std::vector<vk::ExtensionProperties> availableExtensions;
    if (!vulkanExtensible->TryGetAvailableExtensions(availableExtensions))
        return;

    FilterExtensions(requestedExtension, availableExtensions);
}

void VulkanExtensionsValidator::FilterExtensions(std::vector<VulkanExtension> &requestedExtensions,
                                                 const std::vector<vk::ExtensionProperties> &supportedExtensions) {
    for(VulkanExtension& requestedExtension : requestedExtensions) {
        if(std::ranges::any_of(supportedExtensions, [&requestedExtension](const vk::ExtensionProperties& supportedExtension){
            return std::strcmp(requestedExtension.GetExtensionName(), supportedExtension.extensionName) == 0;
        }))
            requestedExtension.MarkSupported();
        else
            requestedExtension.MarkUnsupported();
    }
}
