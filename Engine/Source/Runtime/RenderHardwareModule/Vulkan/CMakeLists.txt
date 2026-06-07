add_library(RenderHardwareModule.Vulkan STATIC)

target_sources(RenderHardwareModule.Vulkan
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
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IVulkanDeviceProvider.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/VulkanGlobals.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/VulkanDeviceProvider.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IVulkanDevice.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/VulkanDevice.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Extensions/VulkanExtension.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Features/DeviceFeature.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Features/DeviceFeatureType.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Features/IDeviceFeaturesAssembler.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Features/DeviceFeaturesAssembler.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IVulkanDeviceFactory.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/VulkanDeviceFactory.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Memory/VulkanMemoryCommon.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Memory/VulkanDeviceMemory.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Memory/IVulkanDeviceAllocator.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Memory/DefaultVulkanDeviceAllocator.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Memory/VulkanMemoryPage.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Memory/VulkanAllocationConfiguration.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Memory/IVulkanDedicatedDeviceAllocator.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Memory/DefaultVulkanDedicatedDeviceAllocator.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Memory/IVulkanDeviceMemoryProvider.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Memory/VulkanDeviceMemoryProvider.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Memory/VulkanResourceTilingType.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Memory/VulkanDeviceAllocatorBundle.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Memory/VulkanMemoryProviderType.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Memory/IVulkanDeviceMemoryProviderFactory.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Memory/VulkanDeviceMemoryProviderFactory.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/VulkanRenderProvider.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Extensions/VulkanExtensionsAssembler.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Injection/Installers/VulkanInstaller.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/ValidationLayers/VulkanLayersValidator.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/ValidationLayers/VulkanDebugAdapter.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Injection/VulkanDependencyContext.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/VulkanDeviceProvider.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/VulkanDevice.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Extensions/DeviceExtension.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Features/DeviceFeature.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Features/DeviceFeaturesAssembler.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/VulkanDeviceFactory.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Memory/VulkanMemoryCommon.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Memory/VulkanDeviceMemory.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Memory/DefaultVulkanDeviceAllocator.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Memory/VulkanMemoryPage.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Memory/DefaultVulkanDedicatedDeviceAllocator.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Memory/VulkanDeviceMemoryProvider.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Memory/VulkanDeviceAllocatorBundle.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Memory/VulkanDeviceMemoryProviderFactory.cpp
)


if(WIN32)
    target_sources(RenderHardwareModule.Vulkan
            PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Extensions/VulkanWindowsExtensionsProvider.h
            PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Extensions/VulkanWindowsExtensionsProvider.cpp
    )
else()
    target_sources(RenderHardwareModule.Vulkan
            PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Extensions/VulkanMockExtensionsProvider.h
    )
endif()

target_include_directories(RenderHardwareModule.Vulkan
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(RenderHardwareModule.Vulkan
        PUBLIC
        vulkan
        CoreModule.Common
        MemoryModule
        PRIVATE
        RenderHardwareModule.Core
        InjectionModule.Core
        DebugModule
        MathModule
)

if(MSVC)
    target_compile_options(RenderHardwareModule.Vulkan PRIVATE /W4)
else()
    target_compile_options(RenderHardwareModule.Vulkan PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(RenderHardwareModule.Vulkan PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
