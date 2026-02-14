add_library(RenderProviderModule.Core.Mock STATIC)

target_sources(RenderProviderModule.Core.Mock
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Public/MockRenderProviderFactory.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Public/MockRenderPriorityQueue.h
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Private/MockRenderProviderFactory.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Private/MockRenderPriorityQueue.cpp
)

target_include_directories(RenderProviderModule.Core.Mock
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(RenderProviderModule.Core.Mock
        PRIVATE
        RenderProviderModule.Core
)

if(MSVC)
    target_compile_options(RenderProviderModule.Core.Mock PRIVATE /W4)
else()
    target_compile_options(RenderProviderModule.Core.Mock PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(RenderProviderModule.Core.Mock PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
