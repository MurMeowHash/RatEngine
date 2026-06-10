add_library(RHLModule.Core STATIC)

target_sources(RHLModule.Core
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IRHLProvider.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/RHLProviderExecResult.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IRHLProviderFactory.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/RenderingApi.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/RHLRuntimeData.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Configurations/RenderApi/RenderApiPriorityConfiguration.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Configurations/RenderApi/RenderApiConfiguration.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/RHLProviderExecResult.cpp
)

target_include_directories(RHLModule.Core
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(RHLModule.Core
        PUBLIC
        CoreModule.Common
)

if(MSVC)
    target_compile_options(RHLModule.Core PRIVATE /W4)
else()
    target_compile_options(RHLModule.Core PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(RHLModule.Core PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
