#pragma once
#include "IVulkanInstance.h"
#include "Entity/VulkanEntity.h"
#include "Extensions/IVulkanExtensionsValidator.h"
#include "ValidationLayers/IVulkanDebugAdapter.h"
#include "ValidationLayers/IVulkanLayersValidator.h"

class ProjectSettings;
class Application;

class VulkanInstance : public VulkanEntity, public IVulkanInstance {
public:
    [[nodiscard]] bool TryGetAvailableExtensions(std::vector<vk::ExtensionProperties> &availableExtensions) const override;
public:
    VulkanInstance(IVulkanExtensionsValidator* vulkanExtensionValidator, IVulkanLayersValidator* vulkanLayersValidator,
        IVulkanDebugAdapter* vulkanDebugAdapter, ProjectSettings* projectSettings, Application* application);

    [[nodiscard]] bool Initialize(const VulkanInstanceInitializationInfo& initializationInfo) override;
    [[nodiscard]] vk::raii::Instance& GetHandle() override;
private:
    IVulkanLayersValidator* m_vulkanLayersValidator;
    IVulkanDebugAdapter* m_vulkanDebugAdapter;

    ProjectSettings* m_projectSettings;
    Application* m_application;

    vk::raii::Context m_vulkanContext;
    vk::raii::Instance m_handle = nullptr;
    vk::raii::DebugUtilsMessengerEXT m_vulkanDebugMessanger = nullptr;

    bool InitializeVulkanDebug();
};
