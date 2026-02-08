#pragma once

struct VulkanApiVersion {
    int m_versionVariant;
    int m_versionMajor;
    int m_versionMinor;
    int m_versionPatch;
};

struct VulkanSettings {
    VulkanApiVersion m_apiVersion;
    bool m_validationEnabled;
};

struct ApplicationVersion {
    int m_engineVersionMajor;
    int m_engineVersionMinor;
    int m_engineVersionPatch;
};

//TODO: lacks initialization
class Application {
public:
    [[nodiscard]] const char* GetEngineName() const { return m_engineName; }
    [[nodiscard]] ApplicationVersion GetEngineVersion() const { return m_engineVersion; }
    [[nodiscard]] VulkanApiVersion GetMinSupportedVulkanVersion() const { return m_minSupportedVulkanVersion; }
private:
    const char* m_engineName;
    ApplicationVersion m_engineVersion;
    VulkanApiVersion m_minSupportedVulkanVersion;
};