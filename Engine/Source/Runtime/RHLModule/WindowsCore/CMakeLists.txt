add_library(RHLModule.Core.Windows STATIC)

target_sources(RHLModule.Core.Windows
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Public/WindowsRHLProviderFactory.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/WindowsRHLDependencyContextFactory.h
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Private/WindowsRHLProviderFactory.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/WindowsRHLDependencyContextFactory.cpp
)

target_include_directories(RHLModule.Core.Windows
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(RHLModule.Core.Windows
        PRIVATE
        RHLModule.Core
        RHLModule.Vulkan.Injection
        RHLModule.Vulkan.Core
        InjectionModule.Core
        CoreModule.Common
        RHLModule.Installation
)

if(MSVC)
    target_compile_options(RHLModule.Core.Windows PRIVATE /W4)
else()
    target_compile_options(RHLModule.Core.Windows PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(RHLModule.Core.Windows PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
