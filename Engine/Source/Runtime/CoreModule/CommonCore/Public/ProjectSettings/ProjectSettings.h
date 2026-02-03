#pragma once

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

class ProjectSettings {
public:
    const WindowSettings& GetWindowSettings() const { return m_windowSettings; }
    const GeneralSettings& GetGeneralSettings() const { return m_generalSettings; }

    void SetWindowSettings(const WindowSettings& windowSettings) { m_windowSettings = windowSettings; }
    void SetGeneralSettings(const GeneralSettings& generalSettings) { m_generalSettings = generalSettings; }
private:
    WindowSettings m_windowSettings;
    GeneralSettings m_generalSettings;
};