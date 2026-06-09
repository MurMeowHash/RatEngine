add_library(RenderHardwareModule.Vulkan.Injection STATIC)

target_sources(RenderHardwareModule.Vulkan.Injection
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/VulkanRenderHardwareDependencyContext.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Installers/VulkanHardwareInstaller.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Installers/VulkanConfigurationsInstaller.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/VulkanRenderHardwareDependencyContext.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Installers/VulkanHardwareInstaller.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Installers/VulkanConfigurationsInstaller.cpp
)

target_include_directories(RenderHardwareModule.Vulkan.Injection
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(RenderHardwareModule.Vulkan.Injection
        PRIVATE
        RenderHardwareModule.Lifecycle
        RenderHardwareModule.Vulkan.Core
        InjectionModule.Core
        DebugModule
)

if(WIN32)
    target_link_libraries(RenderHardwareModule.Vulkan.Injection
            PRIVATE
            RenderHardwareModule.Vulkan.Windows
    )
else()
    target_link_libraries(RenderHardwareModule.Vulkan.Injection
            PRIVATE
            RenderHardwareModule.Vulkan.Mock
    )
endif()

if(MSVC)
    target_compile_options(RenderHardwareModule.Vulkan.Injection PRIVATE /W4)
else()
    target_compile_options(RenderHardwareModule.Vulkan.Injection PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(RenderHardwareModule.Vulkan.Injection PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
