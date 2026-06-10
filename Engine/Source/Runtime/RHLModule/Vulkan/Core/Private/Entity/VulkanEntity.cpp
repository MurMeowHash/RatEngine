#include "../../Public/Entity/VulkanEntity.h"

VulkanEntity::VulkanEntity(IVulkanExtensionsValidator *vulkanExtensionsValidator)
: m_vulkanExtensionsValidator(vulkanExtensionsValidator) { }

void VulkanEntity::SetApiVersion(uint32_t apiVersion) {
    m_apiVersion = apiVersion;
}

uint32_t VulkanEntity::GetApiVersion() const {
    return m_apiVersion;
}

bool VulkanEntity::IsExtensionSupported(const char *extensionName) const {
    return IsExtensionSupported(VulkanExtension::EncodeExtensionName(extensionName));
}

bool VulkanEntity::IsExtensionSupported(VulkanExtension::EncodingType extensionEncoding) const {
    auto extensionIterator = m_extensions.find(extensionEncoding);
    if(extensionIterator == m_extensions.end())
        return false;

    return extensionIterator->second.IsSupported();
}

std::vector<const char *> VulkanEntity::GetSupportedExtensionNames() const {
    std::vector<const char*> mandatoryExtensionNames;
    mandatoryExtensionNames.reserve(m_extensions.size());

    for(const std::pair<const VulkanExtension::EncodingType, VulkanExtension>& extensionUnit : m_extensions) {
        if(extensionUnit.second.IsSupported())
            mandatoryExtensionNames.emplace_back(extensionUnit.second.GetExtensionName());
    }

    return mandatoryExtensionNames;
}

void VulkanEntity::ProcessExtensionsRequest(const std::vector<VulkanExtension> &requestedExtensions) {
    std::vector<VulkanExtension> filteredExtensions = requestedExtensions;
    m_vulkanExtensionsValidator->ValidateExtensions(this, filteredExtensions);

    m_extensions.clear();
    for (const VulkanExtension& extension : filteredExtensions) {
        m_extensions.emplace(extension.GetExtensionEncoding(), extension);
    }
}
