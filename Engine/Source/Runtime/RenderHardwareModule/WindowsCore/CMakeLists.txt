add_library(RenderHardwareModule.Core.Windows STATIC)

target_sources(RenderHardwareModule.Core.Windows
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/WindowsRenderProviderFactory.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/WindowsRenderPriorityQueue.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/WindowsRenderProviderFactory.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/WindowsRenderPriorityQueue.cpp
)

target_include_directories(RenderHardwareModule.Core.Windows
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(RenderHardwareModule.Core.Windows
        PRIVATE
        RenderHardwareModule.Core
        RenderHardwareModule.Vulkan
        InjectionModule.Core
        CoreModule.Common
)

if(MSVC)
    target_compile_options(RenderHardwareModule.Core.Windows PRIVATE /W4)
else()
    target_compile_options(RenderHardwareModule.Core.Windows PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(RenderHardwareModule.Core.Windows PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
