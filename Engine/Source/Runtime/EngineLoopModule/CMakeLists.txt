add_library(EngineLoopModule STATIC)

target_sources(EngineLoopModule
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IEngineLoop.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/CoreLoop.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/CoreLoop.cpp
)

target_include_directories(EngineLoopModule
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(EngineLoopModule
        PUBLIC
        InjectionModule.Core
        InjectionModule.Engine
        EventBusModule.Core
        EventBusModule.Engine
        DebugModule
        CoreModule.Common
        WindowProviderModule.Core
)

if(MSVC)
    target_compile_options(EngineLoopModule PRIVATE /W4)
else()
    target_compile_options(EngineLoopModule PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(EngineLoopModule PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
