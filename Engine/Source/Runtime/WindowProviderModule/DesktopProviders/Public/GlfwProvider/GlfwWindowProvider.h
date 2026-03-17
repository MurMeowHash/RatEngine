#pragma once

#include "IWindowProvider.h"

class GLFWwindow;
class IPlatformInteractor;

class GlfwWindowProvider : IWindowProvider {
public:
    explicit GlfwWindowProvider(IPlatformInteractor* platformInteractor);
    Rat::WindowProviderModule::ExecResult CreateMainWindow(const WindowCreateInfo& windowCreateInfo) override;
    void Tick() override;
    void Shutdown() override;

private:
    bool m_isInitialized = false;
    GLFWwindow *m_mainWindow = nullptr;
    IPlatformInteractor* m_platformInteractor = nullptr;
};