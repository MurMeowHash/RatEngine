#pragma once

struct ApplicationVersion {
    int m_engineVersionMajor;
    int m_engineVersionMinor;
    int m_engineVersionPatch;
};

class Application {
public:
    [[nodiscard]] const char* GetEngineName() const { return m_engineName; }
    [[nodiscard]] ApplicationVersion GetEngineVersion() const { return m_engineVersion; }

    void SetEngineName(const char* engineName) { m_engineName = engineName; }
    void SetEngineVersion(const ApplicationVersion& engineVersion) { m_engineVersion = engineVersion; }
private:
    const char* m_engineName;
    ApplicationVersion m_engineVersion;
};