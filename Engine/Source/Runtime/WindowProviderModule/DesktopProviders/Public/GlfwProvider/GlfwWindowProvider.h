#pragma once

#include "IWindowProvider.h"
#include "GLFW/glfw3.h"

class GlfwWindowProvider : IWindowProvider {
public:
    Rat::WindowProviderModule::ExecResult CreateMainWindow(const WindowCreateInfo& windowCreateInfo) override;
    void Tick() override;
    void Shutdown() override;

private:
    bool m_isInitialized = false;
    GLFWwindow *m_mainWindow = nullptr;
};