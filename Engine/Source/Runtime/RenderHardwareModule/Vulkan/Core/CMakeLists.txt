add_library(RenderHardwareModule.Vulkan.Core STATIC)

target_sources(RenderHardwareModule.Vulkan.Core
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/VulkanRenderHardwareProvider.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/ValidationLayers/IVulkanLayersValidator.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/ValidationLayers/VulkanLayersValidator.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/ValidationLayers/IVulkanDebugAdapter.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/ValidationLayers/VulkanDebugAdapter.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IVulkanDeviceProvider.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/VulkanGlobals.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/VulkanDeviceProvider.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IVulkanDevice.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/VulkanDevice.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Extensions/VulkanExtension.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Extensions/IVulkanExtensible.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Extensions/IVulkanExtensionsValidator.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Features/VulkanDeviceFeature.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Features/VulkanDeviceFeatureType.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Features/IVulkanDeviceFeaturesAssembler.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Features/VulkanDeviceFeaturesAssembler.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/IVulkanDeviceFactory.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/VulkanDeviceFactory.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Memory/VulkanMemoryCommon.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Memory/VulkanDeviceMemory.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Memory/IVulkanDeviceAllocator.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Memory/DefaultVulkanDeviceAllocator.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Memory/VulkanMemoryPage.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Memory/IVulkanDedicatedDeviceAllocator.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Memory/DefaultVulkanDedicatedDeviceAllocator.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Memory/IVulkanDeviceMemoryProvider.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Memory/VulkanDeviceMemoryProvider.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Memory/VulkanResourceTilingType.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Memory/VulkanDeviceAllocatorBundle.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Memory/VulkanMemoryProviderType.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Memory/IVulkanDeviceMemoryProviderFactory.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Memory/VulkanDeviceMemoryProviderFactory.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Memory/VulkanMemoryHeap.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Configurations/Extensions/VulkanExtensionsConfiguration.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Configurations/Instance/VulkanInstanceConfiguration.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Configurations/Device/VulkanAllocationPreset.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Configurations/Device/VulkanAllocationConfiguration.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Configurations/Device/VulkanDeviceConfiguration.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Instance/IVulkanInstance.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Instance/VulkanInstance.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Instance/IVulkanInstanceFactory.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Instance/VulkanInstanceFactory.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Entity/IVulkanVersionable.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Entity/VulkanEntity.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Public/Entity/IVulkanEntity.h
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/VulkanRenderHardwareProvider.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/ValidationLayers/VulkanLayersValidator.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/ValidationLayers/VulkanDebugAdapter.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/VulkanDeviceProvider.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/VulkanDevice.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Extensions/VulkanExtension.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Extensions/VulkanExtensionsValidator.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Features/VulkanDeviceFeature.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Features/VulkanDeviceFeaturesAssembler.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/VulkanDeviceFactory.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Memory/VulkanMemoryCommon.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Memory/VulkanDeviceMemory.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Memory/DefaultVulkanDeviceAllocator.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Memory/VulkanMemoryPage.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Memory/DefaultVulkanDedicatedDeviceAllocator.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Memory/VulkanDeviceMemoryProvider.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Memory/VulkanDeviceAllocatorBundle.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Memory/VulkanDeviceMemoryProviderFactory.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Memory/VulkanMemoryHeap.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Instance/VulkanInstance.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Instance/VulkanInstanceFactory.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Private/Entity/VulkanEntity.cpp
)

target_include_directories(RenderHardwareModule.Vulkan.Core
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(RenderHardwareModule.Vulkan.Core
        PUBLIC
        vulkan
        CoreModule.Common
        MemoryModule
        PRIVATE
        RenderHardwareModule.Core
        InjectionModule.Core
        DebugModule
        MathModule
        RenderHardwareModule.Lifecycle
)

if(MSVC)
    target_compile_options(RenderHardwareModule.Vulkan.Core PRIVATE /W4)
else()
    target_compile_options(RenderHardwareModule.Vulkan.Core PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(RenderHardwareModule.Vulkan.Core PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
