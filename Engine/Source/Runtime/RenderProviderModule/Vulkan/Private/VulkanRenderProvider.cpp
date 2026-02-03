#include "../Public/VulkanRenderProvider.h"
#include <vulkan/vulkan_raii.hpp>

VulkanRenderProvider::VulkanRenderProvider(ProjectSettings *projectSettings, Application* application)
: m_projectSettings(projectSettings), m_application(application) {}

void VulkanRenderProvider::Initialize() {

}

void VulkanRenderProvider::CreateVulkanInstance() {
    GeneralSettings appGeneralSettings = m_projectSettings->GetGeneralSettings();
    ApplicationVersion engineVersion = m_application->GetEngineVersion();
    VulkanApiVersion minVulkanApiVersion = m_application->GetMinSupportedVulkanVersion();
    uint32_t minVulkanVersion = VK_MAKE_API_VERSION(minVulkanApiVersion.m_versionVariant,
                                                    minVulkanApiVersion.m_versionMajor,
                                                    minVulkanApiVersion.m_versionMinor,
                                                    minVulkanApiVersion.m_versionPatch);

    m_apiVersion = std::max(minVulkanVersion, GetDriverMaxSupportedVersion());

    vk::ApplicationInfo appInfo;
    appInfo.pApplicationName = appGeneralSettings.m_projectTitle;
    appInfo.applicationVersion = VK_MAKE_VERSION(appGeneralSettings.m_versionMajor,
                                                 appGeneralSettings.m_versionMinor,
                                                 appGeneralSettings.m_versionPatch);
    appInfo.pEngineName = m_application->GetEngineName();
    appInfo.engineVersion = VK_MAKE_VERSION(engineVersion.m_engineVersionMajor,
                                            engineVersion.m_engineVersionMinor,
                                            engineVersion.m_engineVersionPatch);
    appInfo.apiVersion = m_apiVersion;

    vk::InstanceCreateInfo instanceInfo;
    instanceInfo.pApplicationInfo = &appInfo;
}

uint32_t VulkanRenderProvider::GetApiVersion() const {
    return m_apiVersion;
}

uint32_t VulkanRenderProvider::GetDriverMaxSupportedVersion() const {
    return m_vulkanContext.enumerateInstanceVersion();
}