#pragma once
#include "IVulkanExtensionsValidator.h"

class VulkanExtensionsValidator : public IVulkanExtensionsValidator {
public:
    void ValidateInstanceExtensions(const vk::raii::Context& context, std::vector<VulkanExtension> &requestedExtension) override;
    void ValidateDeviceExtensions(const vk::raii::PhysicalDevice& physicalDevice, std::vector<VulkanExtension> &requestedExtension) override;
    void ValidateExtensions(IVulkanExtensible *vulkanExtensible, std::vector<VulkanExtension> &requestedExtension) override;
private:
    void FilterExtensions(std::vector<VulkanExtension> &requestedExtensions, const std::vector<vk::ExtensionProperties>& supportedExtensions);
};
