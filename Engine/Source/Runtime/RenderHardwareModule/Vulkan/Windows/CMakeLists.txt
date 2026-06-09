add_library(RenderHardwareModule.Vulkan.Windows INTERFACE)

target_sources(RenderHardwareModule.Vulkan.Windows
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Public/Configurations/Extensions/WindowsVulkanExtensionsConfiguration.h
)

target_include_directories(RenderHardwareModule.Vulkan.Windows
        INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
)

target_link_libraries(RenderHardwareModule.Vulkan.Windows
        INTERFACE
        vulkan
        RenderHardwareModule.Vulkan.Core
)

if(MSVC)
    target_compile_options(RenderHardwareModule.Vulkan.Windows INTERFACE /W4)
else()
    target_compile_options(RenderHardwareModule.Vulkan.Windows INTERFACE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(RenderHardwareModule.Vulkan.Windows PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
