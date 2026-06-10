add_library(RHLModule.Vulkan.Mock INTERFACE)

target_sources(RHLModule.Vulkan.Mock
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Public/Configurations/Extensions/MockVulkanExtensionsConfiguration.h
)

target_include_directories(RHLModule.Vulkan.Mock
        INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
)

target_link_libraries(RHLModule.Vulkan.Mock
        INTERFACE
        vulkan
        RHLModule.Vulkan.Core
)

if(MSVC)
    target_compile_options(RHLModule.Vulkan.Mock INTERFACE /W4)
else()
    target_compile_options(RHLModule.Vulkan.Mock INTERFACE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(RHLModule.Vulkan.Mock PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
