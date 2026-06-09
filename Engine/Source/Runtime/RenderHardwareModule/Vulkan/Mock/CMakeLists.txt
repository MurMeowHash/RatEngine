add_library(RenderHardwareModule.Vulkan.Mock INTERFACE)

target_sources(RenderHardwareModule.Vulkan.Mock
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Public/Configurations/Extensions/MockVulkanExtensionsConfiguration.h
)

target_include_directories(RenderHardwareModule.Vulkan.Mock
        INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
)

target_link_libraries(RenderHardwareModule.Vulkan.Mock
        INTERFACE
        vulkan
        RenderHardwareModule.Vulkan.Core
)

if(MSVC)
    target_compile_options(RenderHardwareModule.Vulkan.Mock INTERFACE /W4)
else()
    target_compile_options(RenderHardwareModule.Vulkan.Mock INTERFACE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(RenderHardwareModule.Vulkan.Mock PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
