add_library(RenderHardwareModule.Installation STATIC)

target_sources(RenderHardwareModule.Installation
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Public/RenderHardwareEngineModuleInstaller.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Public/RenderHardwareModuleInstaller.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Public/RenderHardwareDependencyContext.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Public/IRenderHardwareDependencyContextFactory.h
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Private/RenderHardwareEngineModuleInstaller.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Private/RenderHardwareModuleInstaller.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Private/RenderHardwareDependencyContext.cpp
)

target_include_directories(RenderHardwareModule.Installation
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(RenderHardwareModule.Installation
        PRIVATE
        RenderHardwareModule.Core
        InjectionModule.Core
)

if(WIN32)
    target_link_libraries(RenderHardwareModule.Installation
            PRIVATE
            RenderHardwareModule.Core.Windows
    )
else()
    target_link_libraries(RenderHardwareModule.Installation
            PRIVATE
            RenderHardwareModule.Core.Mock
    )
endif()

if(MSVC)
    target_compile_options(RenderHardwareModule.Installation PRIVATE /W4)
else()
    target_compile_options(RenderHardwareModule.Installation PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(RenderHardwareModule.Installation PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
