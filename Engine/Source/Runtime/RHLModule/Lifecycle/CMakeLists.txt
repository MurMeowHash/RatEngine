add_library(RHLModule.Lifecycle STATIC)

target_sources(RHLModule.Lifecycle
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/RHLLoop.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/RHLLoop.cpp
)

target_include_directories(RHLModule.Lifecycle
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(RHLModule.Lifecycle
        PRIVATE
        EngineLoopModule.Core
        CoreModule.Common
        RHLModule.Core
        DebugModule
        RHLModule.Installation
        InjectionModule.Core
)

if(MSVC)
    target_compile_options(RHLModule.Lifecycle PRIVATE /W4)
else()
    target_compile_options(RHLModule.Lifecycle PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(RHLModule.Lifecycle PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
