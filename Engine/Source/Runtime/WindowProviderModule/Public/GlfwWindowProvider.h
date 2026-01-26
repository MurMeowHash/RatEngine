#pragma once

#include "IWindowProvider.h"
#include "GLFW/glfw3.h"

class GlfwWindowProvider : IWindowProvider {
public:
    void CreateWindow(WindowCreateInfo windowCreateInfo) override;
private:
    GLFWwindow *m_window;
};