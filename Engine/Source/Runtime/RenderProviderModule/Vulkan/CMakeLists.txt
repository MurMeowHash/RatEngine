add_library(RenderProviderModule.Vulkan STATIC)

target_sources(RenderProviderModule.Vulkan
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/VulkanRenderProvider.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/VulkanRenderProvider.cpp
)

target_include_directories(RenderProviderModule.Vulkan
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(RenderProviderModule.Vulkan
        PRIVATE
        RenderProviderModule.Core
        vulkan
        CoreModule.Common
)

if(MSVC)
    target_compile_options(RenderProviderModule.Vulkan PRIVATE /W4)
else()
    target_compile_options(RenderProviderModule.Vulkan PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(RenderProviderModule.Vulkan PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
