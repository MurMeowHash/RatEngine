add_library(WindowProviderModule.Installation STATIC)

target_sources(WindowProviderModule.Installation
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/WindowProviderModuleInstaller.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/WindowProviderModuleInstaller.cpp
)

target_include_directories(WindowProviderModule.Installation
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(WindowProviderModule.Installation
        PRIVATE
            InjectionModule.Core
            WindowProviderModule.Core
)

if(WIN32 OR APPLE OR UNIX)
    target_link_libraries(WindowProviderModule.Installation
            PRIVATE
            WindowProviderModule.Desktop
    )
else()
    target_link_libraries(WindowProviderModule.Installation
            PRIVATE
            WindowProviderModule.Mock
    )
endif()

if(MSVC)
    target_compile_options(WindowProviderModule.Installation PRIVATE /W4)
else()
    target_compile_options(WindowProviderModule.Installation PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(WindowProviderModule.Installation PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
