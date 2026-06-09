add_library(RenderHardwareModule.Core STATIC)

target_sources(RenderHardwareModule.Core
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IRenderHardwareProvider.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/RenderHardwareProviderExecResult.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IRenderHardwareProviderFactory.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/RenderingApi.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/RenderHardwareRuntimeData.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Configurations/RenderApi/RenderApiPriorityConfiguration.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Configurations/RenderApi/RenderApiConfiguration.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/RenderHardwareProviderExecResult.cpp
)

target_include_directories(RenderHardwareModule.Core
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(RenderHardwareModule.Core
        PUBLIC
        CoreModule.Common
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
