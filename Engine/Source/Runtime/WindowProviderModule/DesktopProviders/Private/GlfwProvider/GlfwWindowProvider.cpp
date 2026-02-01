#include "../Public/GlfwProvider/GlfwWindowProvider.h"
#include "GLFW/glfw3.h"

Rat::WindowProviderModule::ExecResult GlfwWindowProvider::CreateMainWindow(const WindowCreateInfo& windowCreateInfo) {
    if(!m_isInitialized) {
        if(glfwInit() == GLFW_TRUE)
            m_isInitialized = true;
        else
            return Rat::WindowProviderModule::ExecResult::APIInitializationFailure;
    }

    if(m_mainWindow != nullptr)
        return Rat::WindowProviderModule::ExecResult::WindowAlreadyCreated;

    GLFWmonitor *requestedMonitor = nullptr;
    if(windowCreateInfo.m_fullScreen)
        requestedMonitor = glfwGetPrimaryMonitor();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    m_mainWindow = glfwCreateWindow(windowCreateInfo.m_width,
                                    windowCreateInfo.m_height,
                                    windowCreateInfo.m_title,
                                    requestedMonitor,
                                    nullptr);

    return m_mainWindow == nullptr
    ? Rat::WindowProviderModule::ExecResult::WindowCreationFailure
    : Rat::WindowProviderModule::ExecResult::Success;
}

void GlfwWindowProvider::Tick() {
    glfwPollEvents();
}

void GlfwWindowProvider::Shutdown() {
    glfwDestroyWindow(m_mainWindow);
    glfwTerminate();

    m_isInitialized = false;
    m_mainWindow = nullptr;
}
