#pragma once

#include "IRenderProvider.h"
#include <vulkan/vulkan_raii.hpp>
#include "ProjectSettings/ProjectSettings.h"
#include "Application/Application.h"

class VulkanRenderProvider : IRenderProvider {
public:
    VulkanRenderProvider(ProjectSettings* projectSettings, Application* application);
    void Initialize() override;
    [[nodiscard]] uint32_t GetDriverMaxSupportedVersion() const override;
    [[nodiscard]] uint32_t GetApiVersion() const override;
private:
    ProjectSettings* m_projectSettings = nullptr;
    Application* m_application = nullptr;

    uint32_t m_apiVersion = 0;

    vk::raii::Context m_vulkanContext;
    vk::raii::Instance m_vulkanInstance = nullptr;
    void CreateVulkanInstance();
};