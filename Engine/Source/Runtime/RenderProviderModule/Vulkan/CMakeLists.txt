add_library(RenderProviderModule.Vulkan STATIC)

target_sources(RenderProviderModule.Vulkan
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/VulkanRenderProvider.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Extensions/IVulkanExtensionsAssembler.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Extensions/VulkanExtensionsAssembler.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Extensions/IVulkanPlatformExtensionsProvider.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Injection/Installers/VulkanInstaller.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/ValidationLayers/IVulkanLayersValidator.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/ValidationLayers/VulkanLayersValidator.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/ValidationLayers/IVulkanDebugAdapter.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/ValidationLayers/VulkanDebugAdapter.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Injection/VulkanDependencyContext.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Extensions/ExtensionAssembleFlags.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/VulkanRenderProvider.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Extensions/VulkanExtensionsAssembler.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Injection/Installers/VulkanInstaller.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/ValidationLayers/VulkanLayersValidator.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/ValidationLayers/VulkanDebugAdapter.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Injection/VulkanDependencyContext.cpp
)

if(WIN32)
    target_sources(RenderProviderModule.Vulkan
            PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Extensions/VulkanWindowsExtensionsProvider.h
            PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Extensions/VulkanWindowsExtensionsProvider.cpp
    )
else()
    target_sources(RenderProviderModule.Vulkan
            PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Extensions/VulkanMockExtensionsProvider.h
    )
endif()

target_include_directories(RenderProviderModule.Vulkan
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(RenderProviderModule.Vulkan
        PUBLIC
        vulkan
        PRIVATE
        RenderProviderModule.Core
        CoreModule.Common
        InjectionModule.Core
        DebugModule
)

if(MSVC)
    target_compile_options(RenderProviderModule.Vulkan PRIVATE /W4)
else()
    target_compile_options(RenderProviderModule.Vulkan PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(RenderProviderModule.Vulkan PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
