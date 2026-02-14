#pragma once

class BuildSettings {
public:
    void SetIsDevelopmentBuild(bool isDevelopment);
    [[nodiscard]] bool GetIsDevelopmentBuild() const;
private:
    bool m_isDevelopmentBuild;
};