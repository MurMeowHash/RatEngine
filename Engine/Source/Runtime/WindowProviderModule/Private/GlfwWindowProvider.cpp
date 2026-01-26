#include "GlfwWindowProvider.h"

void GlfwWindowProvider::CreateWindow(WindowCreateInfo windowCreateInfo) {
    if(glfwInit() != GLFW_TRUE)
        
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
}