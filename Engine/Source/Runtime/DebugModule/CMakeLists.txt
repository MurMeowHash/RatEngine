add_library(DebugModule STATIC)

target_sources(DebugModule
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/ILogger.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/EngineLogger.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Installers/DebugModuleInstaller.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/EngineLogger.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Installers/DebugModuleInstaller.cpp
)

target_include_directories(DebugModule
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(DebugModule
        PRIVATE
        InjectionModule.Core
)

if(MSVC)
    target_compile_options(DebugModule PRIVATE /W4)
else()
    target_compile_options(DebugModule PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(DebugModule PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
