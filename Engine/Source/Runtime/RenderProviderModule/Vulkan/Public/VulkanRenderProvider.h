#pragma once

#include "IRenderProvider.h"
#define VULKAN_HPP_NO_EXCEPTIONS
#include <vulkan/vulkan_raii.hpp>
#include "Extensions/IVulkanExtensionsAssembler.h"
#include "ValidationLayers/IVulkanLayersValidator.h"
#include "ValidationLayers/IVulkanDebugAdapter.h"

class ProjectSettings;
class Application;

class VulkanRenderProvider : IRenderProvider {
public:
    VulkanRenderProvider(ProjectSettings* projectSettings, Application* application,
                         IVulkanExtensionsAssembler* vulkanExtensionsAssembler, IVulkanLayersValidator* vulkanLayersValidator,
                         IVulkanDebugAdapter* vulkanDebugAdapter);
    Rat::RenderProviderModule::ExecResult Initialize() override;
    [[nodiscard]] uint32_t GetApiVersion() const override;
    [[nodiscard]] bool CanContinueExecution(const Rat::RenderProviderModule::ExecResult &execResult) const override;
private:
    ProjectSettings* m_projectSettings = nullptr;
    Application* m_application = nullptr;
    IVulkanExtensionsAssembler* m_vulkanExtensionsAssembler;
    IVulkanLayersValidator* m_vulkanLayersValidator;
    IVulkanDebugAdapter* m_vulkanDebugAdapter;

    uint32_t m_apiVersion = 0;

    vk::raii::Context m_vulkanContext;
    vk::raii::Instance m_vulkanInstance = nullptr;
    vk::raii::DebugUtilsMessengerEXT m_vulkanDebugMessanger = nullptr;
    Rat::RenderProviderModule::ExecResult CreateVulkanInstance();
    Rat::RenderProviderModule::ExecResult InitializeVulkanDebug();
};