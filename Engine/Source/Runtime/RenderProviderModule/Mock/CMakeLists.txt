add_library(RenderProviderModule.Mock INTERFACE)

target_sources(RenderProviderModule.Mock
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/MockRenderProvider.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Installers/MockRenderModuleInstaller.h
)

target_include_directories(RenderProviderModule.Mock
        INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
)

target_link_libraries(RenderProviderModule.Mock
        INTERFACE
        RenderProviderModule.Core
        InjectionModule.Core
)

if(MSVC)
    target_compile_options(RenderProviderModule.Mock INTERFACE /W4)
else()
    target_compile_options(RenderProviderModule.Mock INTERFACE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(RenderProviderModule.Mock PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
