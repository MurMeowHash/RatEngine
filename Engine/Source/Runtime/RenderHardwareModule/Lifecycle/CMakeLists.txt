add_library(RenderHardwareModule.Lifecycle STATIC)

target_sources(RenderHardwareModule.Lifecycle
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/RenderHardwareLoop.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/RenderHardwareLoop.cpp
)

target_include_directories(RenderHardwareModule.Lifecycle
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(RenderHardwareModule.Lifecycle
        PRIVATE
        EngineLoopModule.Core
        CoreModule.Common
        RenderHardwareModule.Core
        DebugModule
        RenderHardwareModule.Installation
        InjectionModule.Core
)

if(MSVC)
    target_compile_options(RenderHardwareModule.Lifecycle PRIVATE /W4)
else()
    target_compile_options(RenderHardwareModule.Lifecycle PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(RenderHardwareModule.Lifecycle PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
