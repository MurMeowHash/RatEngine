#pragma once

#include "IRenderProvider.h"
#define VULKAN_HPP_NO_EXCEPTIONS
#include <vulkan/vulkan_raii.hpp>
#include "Extensions/IVulkanExtensionsAssembler.h"
#include "ValidationLayers/IVulkanLayersValidator.h"
#include "ValidationLayers/IVulkanDebugAdapter.h"
#include "Injection/VulkanDependencyContext.h"

class ProjectSettings;
class Application;
class BuildSettings;

class VulkanRenderProvider : public IRenderProvider {
public:
    VulkanRenderProvider(ProjectSettings* projectSettings, Application* application, BuildSettings* buildSettings,
                         const DiContainer* diContainer);
    Rat::RenderProviderModule::ExecResult Initialize() override;
    void Shutdown() override;
    [[nodiscard]] uint32_t GetApiVersion() const override;
    [[nodiscard]] bool CanContinueExecution(const Rat::RenderProviderModule::ExecResult &execResult) const override;

    ~VulkanRenderProvider() override;
private:
    VulkanDependencyContext* m_vulkanDependencyContext = nullptr;

    ProjectSettings* m_projectSettings = nullptr;
    Application* m_application = nullptr;
    BuildSettings* m_buildSettings = nullptr;
    IVulkanExtensionsAssembler* m_vulkanExtensionsAssembler = nullptr;
    IVulkanLayersValidator* m_vulkanLayersValidator = nullptr;
    IVulkanDebugAdapter* m_vulkanDebugAdapter = nullptr;
    const DiContainer* m_diContainer = nullptr;

    uint32_t m_apiVersion = 0;

    vk::raii::Context m_vulkanContext;
    vk::raii::Instance m_vulkanInstance = nullptr;
    vk::raii::DebugUtilsMessengerEXT m_vulkanDebugMessanger = nullptr;
    Rat::RenderProviderModule::ExecResult CreateVulkanInstance();
    Rat::RenderProviderModule::ExecResult InitializeVulkanDebug();
    void AcquireInternalDependencies();
};