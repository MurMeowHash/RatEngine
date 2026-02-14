add_library(RenderProviderModule.Core STATIC)

target_sources(RenderProviderModule.Core
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

target_include_directories(RenderProviderModule.Core
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(RenderProviderModule.Core
)

if(MSVC)
    target_compile_options(RenderProviderModule.Core PRIVATE /W4)
else()
    target_compile_options(RenderProviderModule.Core PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(RenderProviderModule.Core PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
