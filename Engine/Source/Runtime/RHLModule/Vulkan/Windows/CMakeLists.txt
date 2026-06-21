add_library(RHLModule.Vulkan.Windows INTERFACE)

target_sources(RHLModule.Vulkan.Windows
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Public/Configurations/Extensions/WindowsVulkanExtensionsConfiguration.h
)

target_include_directories(RHLModule.Vulkan.Windows
        INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
)

target_link_libraries(RHLModule.Vulkan.Windows
        INTERFACE
        vulkan
        RHLModule.Vulkan.Core
)

if(MSVC)
    target_compile_options(RHLModule.Vulkan.Windows INTERFACE /W4)
else()
    target_compile_options(RHLModule.Vulkan.Windows INTERFACE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(RHLModule.Vulkan.Windows PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
