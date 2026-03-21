add_library(ConcurrencyModule.CommandBuffers INTERFACE)

target_sources(ConcurrencyModule.CommandBuffers
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/ConcurrencyCommandBuffer.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IConcurrencyCommandBufferPool.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/ConcurrencyCommandBufferPool.h
)

target_include_directories(ConcurrencyModule.CommandBuffers
        INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
)

target_link_libraries(ConcurrencyModule.CommandBuffers
        INTERFACE
        DelegateModule
        MemoryModule
        CoreModule.Common
)

if(MSVC)
    target_compile_options(ConcurrencyModule.CommandBuffers INTERFACE /W4)
else()
    target_compile_options(ConcurrencyModule.CommandBuffers INTERFACE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(ConcurrencyModule.CommandBuffers PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
