add_library(RHLModule.Core.Mock STATIC)

target_sources(RHLModule.Core.Mock
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Public/MockRHLProviderFactory.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Public/MockRHLDependencyContextFactory.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Public/MockRHLDependencyContext.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Public/MockRHLProvider.h
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Private/MockRHLProviderFactory.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Private/MockRHLDependencyContextFactory.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Private/MockRHLDependencyContext.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Private/MockRHLProvider.cpp
)

target_include_directories(RHLModule.Core.Mock
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(RHLModule.Core.Mock
        PRIVATE
        RHLModule.Core
        RHLModule.Installation
        InjectionModule.Core
)

if(MSVC)
    target_compile_options(RHLModule.Core.Mock PRIVATE /W4)
else()
    target_compile_options(RHLModule.Core.Mock PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(RHLModule.Core.Mock PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
