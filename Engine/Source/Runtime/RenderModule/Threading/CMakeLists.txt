add_library(RenderModule.Threading STATIC)

target_sources(RenderModule.Threading
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/RenderThread.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/RenderConcurrencyCommandBuffer.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/RenderThread.cpp
)

target_include_directories(RenderModule.Threading
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(RenderModule.Threading
        PRIVATE
        ConcurrencyModule.Core
        CoreModule.Common
        ConcurrencyModule.CommandBuffers
        ConcurrencyModule.SynchronizationCommon
)

if(MSVC)
    target_compile_options(RenderModule.Threading PRIVATE /W4)
else()
    target_compile_options(RenderModule.Threading PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(RenderModule.Threading PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
