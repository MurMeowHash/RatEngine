#pragma once

#include <vector>
#include <cstdint>

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

struct VulkanRenderingSettings {
    std::vector<const char*> m_validationLayersNames;
};

struct RenderingSettings {
    VulkanRenderingSettings m_vulkanRenderingSettings;
    int m_maxFramesInFlight;
};

struct MemoryAllocationSettings {
    uint64_t m_defaultChunkSize;
};

class ProjectSettings {
public:
    const WindowSettings& GetWindowSettings() const { return m_windowSettings; }
    const GeneralSettings& GetGeneralSettings() const { return m_generalSettings; }
    const RenderingSettings& GetRenderingSettings() const { return m_renderingSettings; }
    const MemoryAllocationSettings GetMemoryAllocationSettings() const { return m_memoryAllocationSettings; }

    void SetWindowSettings(const WindowSettings& windowSettings) { m_windowSettings = windowSettings; }
    void SetGeneralSettings(const GeneralSettings& generalSettings) { m_generalSettings = generalSettings; }
    void SetRenderingSettings(const RenderingSettings& renderingSettings) { m_renderingSettings = renderingSettings; }
    void SetMemoryAllocationSettings(const MemoryAllocationSettings& memoryAllocationSettings) { m_memoryAllocationSettings = memoryAllocationSettings; }
private:
    WindowSettings m_windowSettings;
    GeneralSettings m_generalSettings;
    RenderingSettings m_renderingSettings;
    MemoryAllocationSettings m_memoryAllocationSettings;
};