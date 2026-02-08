add_library(RenderProviderModule.Core INTERFACE)

target_sources(RenderProviderModule.Core
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IRenderProvider.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/RenderProviderExecResult.h
)

target_include_directories(RenderProviderModule.Core
        INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
)

target_link_libraries(RenderProviderModule.Core
)

if(MSVC)
    target_compile_options(RenderProviderModule.Core INTERFACE /W4)
else()
    target_compile_options(RenderProviderModule.Core INTERFACE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(RenderProviderModule.Core PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
