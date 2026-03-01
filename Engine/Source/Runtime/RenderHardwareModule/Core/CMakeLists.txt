add_library(RenderHardwareModule.Core STATIC)

target_sources(RenderHardwareModule.Core
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IRenderProvider.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/RenderProviderExecResult.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IRenderProviderFactory.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/RenderingApi.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/RenderProviderAccessor.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IRenderProviderInitializer.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/RenderProviderInitializer.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IRenderPriorityQueue.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/RenderProviderInitializer.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/RenderProviderExecResult.cpp
)

target_include_directories(RenderHardwareModule.Core
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(RenderHardwareModule.Core
)

if(MSVC)
    target_compile_options(RenderHardwareModule.Core PRIVATE /W4)
else()
    target_compile_options(RenderHardwareModule.Core PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(RenderHardwareModule.Core PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
