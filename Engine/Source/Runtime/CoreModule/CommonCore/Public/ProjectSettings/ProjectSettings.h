#pragma once

#include <vector>

struct WindowSettings {
    int m_windowWidth;
    int m_windowHeight;
    bool m_isFullscreen;
};

struct GeneralSettings {
    const char* m_projectTitle;
    int m_versionMajor;
    int m_versionMinor;
    int m_versionPatch;
};

enum class RenderingApi {
    None = 0,
    Vulkan = 1
};

struct VulkanRenderingSettings {
    std::vector<const char*> m_validationLayersNames;
};

struct RenderingSettings {
    RenderingApi m_renderingApi;
    VulkanRenderingSettings m_vulkanRenderingSettings;
};

class ProjectSettings {
public:
    const WindowSettings& GetWindowSettings() const { return m_windowSettings; }
    const GeneralSettings& GetGeneralSettings() const { return m_generalSettings; }
    const RenderingSettings& GetRenderingSettings() const { return m_renderingSettings; }

    void SetWindowSettings(const WindowSettings& windowSettings) { m_windowSettings = windowSettings; }
    void SetGeneralSettings(const GeneralSettings& generalSettings) { m_generalSettings = generalSettings; }
    void SetRenderingSettings(const RenderingSettings& renderingSettings) { m_renderingSettings = renderingSettings; }
private:
    WindowSettings m_windowSettings;
    GeneralSettings m_generalSettings;
    RenderingSettings m_renderingSettings;
};