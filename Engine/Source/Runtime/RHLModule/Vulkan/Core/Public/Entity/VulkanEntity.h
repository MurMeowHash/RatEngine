#pragma once

#include <unordered_map>
#include <vector>

#include "IVulkanEntity.h"
#include "Extensions/IVulkanExtensionsValidator.h"

class VulkanEntity : public IVulkanEntity {
public:
    explicit VulkanEntity(IVulkanExtensionsValidator* vulkanExtensionsValidator);
    void SetApiVersion(uint32_t apiVersion) override;
    [[nodiscard]] uint32_t GetApiVersion() const override;

public:
    [[nodiscard]] bool IsExtensionSupported(const char *extensionName) const override;
    [[nodiscard]] bool IsExtensionSupported(VulkanExtension::EncodingType extensionEncoding) const override;
    [[nodiscard]] std::vector<const char *> GetSupportedExtensionNames() const override;

protected:
    void ProcessExtensionsRequest(const std::vector<VulkanExtension>& requestedExtensions);

private:
    IVulkanExtensionsValidator* m_vulkanExtensionsValidator;

    uint32_t m_apiVersion = 0;
    std::unordered_map<VulkanExtension::EncodingType, VulkanExtension> m_extensions;
};
