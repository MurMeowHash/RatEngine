add_library(RenderHardwareModule.Core.Mock STATIC)

target_sources(RenderHardwareModule.Core.Mock
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Public/MockRenderProviderFactory.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Public/MockRenderPriorityQueue.h
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Private/MockRenderProviderFactory.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Private/MockRenderPriorityQueue.cpp
)

target_include_directories(RenderHardwareModule.Core.Mock
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(RenderHardwareModule.Core.Mock
        PRIVATE
        RenderHardwareModule.Core
)

if(MSVC)
    target_compile_options(RenderHardwareModule.Core.Mock PRIVATE /W4)
else()
    target_compile_options(RenderHardwareModule.Core.Mock PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(RenderHardwareModule.Core.Mock PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
