#include "../../Public/ProjectSettings/HardCodedProjectSettingsInitializer.h"
#include <vector>

HardCodedProjectSettingsInitializer::HardCodedProjectSettingsInitializer(ProjectSettings* projectSettings)
: m_projectSettings(projectSettings) { }

void HardCodedProjectSettingsInitializer::Initialize() {
    GeneralSettings generalSettings = GeneralSettings("RatEngine");
    WindowSettings windowSettings = WindowSettings(800, 600, false);
    VulkanRenderingSettings vulkanRenderingSettings = VulkanRenderingSettings;
    vulkanRenderingSettings.m_validationLayersNames = std::vector<const char*>{"VK_LAYER_KHRONOS_validation"};
    RenderingSettings renderingSettings = RenderingSettings(RenderingApi::Vulkan, vulkanRenderingSettings);
    m_projectSettings->SetGeneralSettings(generalSettings);
    m_projectSettings->SetWindowSettings(windowSettings);
    m_projectSettings->SetRenderingSettings(renderingSettings);
}