add_library(RHLModule.Installation STATIC)

target_sources(RHLModule.Installation
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Public/RHLEngineModuleInstaller.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Public/RHLModuleInstaller.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Public/RHLDependencyContext.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Public/IRHLDependencyContextFactory.h
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Private/RHLEngineModuleInstaller.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Private/RHLModuleInstaller.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Private/RHLDependencyContext.cpp
)

target_include_directories(RHLModule.Installation
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(RHLModule.Installation
        PRIVATE
        RHLModule.Core
        InjectionModule.Core
)

if(WIN32)
    target_link_libraries(RHLModule.Installation
            PRIVATE
            RHLModule.Core.Windows
    )
else()
    target_link_libraries(RHLModule.Installation
            PRIVATE
            RHLModule.Core.Mock
    )
endif()

if(MSVC)
    target_compile_options(RHLModule.Installation PRIVATE /W4)
else()
    target_compile_options(RHLModule.Installation PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(RHLModule.Installation PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
