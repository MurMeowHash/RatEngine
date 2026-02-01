add_library(CoreModule.Installation STATIC)

target_sources(CoreModule.Installation
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Public/CoreModuleInstaller.h
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Private/CoreModuleInstaller.cpp
)

target_include_directories(CoreModule.Installation
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(CoreModule.Installation
        PRIVATE
        InjectionModule.Core
        CoreModule.Common
)

if(WIN32)
    target_link_libraries(CoreModule.Installation
            PRIVATE
            CoreModule.Windows
    )
else()
    target_link_libraries(CoreModule.Installation
            PRIVATE
            CoreModule.Mock
    )
endif()

if(MSVC)
    target_compile_options(CoreModule.Installation PRIVATE /W4)
else()
    target_compile_options(CoreModule.Installation PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(CoreModule.Installation PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
