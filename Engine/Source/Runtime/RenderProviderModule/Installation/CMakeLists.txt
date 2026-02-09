add_library(RenderProviderModule.Installation STATIC)

target_sources(RenderProviderModule.Installation
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/RenderProviderModuleInstaller.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/RenderProviderModuleInstaller.cpp
)

target_include_directories(RenderProviderModule.Installation
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(RenderProviderModule.Installation
        PRIVATE
        RenderProviderModule.Core
        InjectionModule.Core
)

if(WIN32 OR APPLE OR UNIX)
    target_link_libraries(RenderProviderModule.Installation
            PRIVATE
            RenderProviderModule.Vulkan
    )
else()
    target_link_libraries(RenderProviderModule.Installation
            PRIVATE
            RenderProviderModule.Mock
    )
endif()

if(MSVC)
    target_compile_options(RenderProviderModule.Installation PRIVATE /W4)
else()
    target_compile_options(RenderProviderModule.Installation PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(RenderProviderModule.Installation PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
