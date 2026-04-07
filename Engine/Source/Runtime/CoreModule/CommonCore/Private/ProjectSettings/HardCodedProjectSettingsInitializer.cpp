#include "../../Public/ProjectSettings/HardCodedProjectSettingsInitializer.h"
#include <vector>

HardCodedProjectSettingsInitializer::HardCodedProjectSettingsInitializer(ProjectSettings* projectSettings)
: m_projectSettings(projectSettings) { }

void HardCodedProjectSettingsInitializer::Initialize() {
    GeneralSettings generalSettings = GeneralSettings("Render Sample");
    WindowSettings windowSettings = WindowSettings(800, 600, false);
    VulkanRenderingSettings vulkanRenderingSettings = VulkanRenderingSettings();
    vulkanRenderingSettings.m_validationLayersNames = std::vector<const char*>{"VK_LAYER_KHRONOS_validation"};
    RenderingSettings renderingSettings = RenderingSettings(vulkanRenderingSettings, 1);
    MemoryAllocationSettings memoryAllocationSettings = MemoryAllocationSettings(4 * 1024, 16 * 1024);
    m_projectSettings->SetGeneralSettings(generalSettings);
    m_projectSettings->SetWindowSettings(windowSettings);
    m_projectSettings->SetRenderingSettings(renderingSettings);
    m_projectSettings->SetMemoryAllocationSettings(memoryAllocationSettings);
}