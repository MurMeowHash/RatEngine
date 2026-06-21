add_library(RHLModule.Vulkan.Injection STATIC)

target_sources(RHLModule.Vulkan.Injection
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/VulkanRHLDependencyContext.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Installers/VulkanHardwareInstaller.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Installers/VulkanConfigurationsInstaller.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/VulkanRHLDependencyContext.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Installers/VulkanHardwareInstaller.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Installers/VulkanConfigurationsInstaller.cpp
)

target_include_directories(RHLModule.Vulkan.Injection
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(RHLModule.Vulkan.Injection
        PRIVATE
        RHLModule.Lifecycle
        RHLModule.Vulkan.Core
        RHLModule.Installation
        InjectionModule.Core
        DebugModule
)

if(WIN32)
    target_link_libraries(RHLModule.Vulkan.Injection
            PRIVATE
            RHLModule.Vulkan.Windows
    )
else()
    target_link_libraries(RHLModule.Vulkan.Injection
            PRIVATE
            RHLModule.Vulkan.Mock
    )
endif()

if(MSVC)
    target_compile_options(RHLModule.Vulkan.Injection PRIVATE /W4)
else()
    target_compile_options(RHLModule.Vulkan.Injection PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(RHLModule.Vulkan.Injection PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
