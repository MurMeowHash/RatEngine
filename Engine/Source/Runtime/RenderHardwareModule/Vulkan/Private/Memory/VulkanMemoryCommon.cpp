#include "../../Public/Memory/VulkanMemoryCommon.h"

namespace Rat::VulkanMemoryCommon {
    VulkanDeviceMemory AllocateDeviceMemory(const vk::raii::Device& device, vk::DeviceSize memSize, uint32_t memoryTypeIndex,
        VkMemoryDedicatedAllocateInfo* dedicatedAllocationInfo) {
        VkMemoryAllocateInfo memoryAllocateInfo;
        memoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        memoryAllocateInfo.allocationSize = memSize;
        memoryAllocateInfo.memoryTypeIndex = memoryTypeIndex;
        memoryAllocateInfo.pNext = dedicatedAllocationInfo;
        VkDeviceMemory allocatedMemory;
        VkResult allocationResult = vkAllocateMemory(*device, &memoryAllocateInfo, nullptr, &allocatedMemory);
        if (allocationResult != VK_SUCCESS)
            return VulkanDeviceMemory();

        VulkanDeviceMemoryInitializer memoryInitializer;
        memoryInitializer.m_handle = allocatedMemory;
        memoryInitializer.m_offset = 0;
        memoryInitializer.m_alignmentOffset = 0;
        memoryInitializer.m_size = memSize;
        memoryInitializer.m_memoryTypeIndex = memoryTypeIndex;
        memoryInitializer.m_dedicated = dedicatedAllocationInfo != nullptr
            && (dedicatedAllocationInfo->image != nullptr || dedicatedAllocationInfo->buffer != nullptr);
        return VulkanDeviceMemory(memoryInitializer);
    }

    void FreeDeviceMemory(const vk::raii::Device& device, VulkanDeviceMemory &memory) {
        vkFreeMemory(*device, memory.GetHandle(), nullptr);
        memory.InvalidateMemory();
    }

    VulkanDeviceMemory AllocateDedicatedImageMemory(const vk::raii::Device &device, const vk::raii::Image& image,
        uint32_t memoryTypeIndex) {
        VkMemoryDedicatedAllocateInfo dedicatedMemoryAllocateInfo;
        dedicatedMemoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO;
        dedicatedMemoryAllocateInfo.image = *image;
        vk::MemoryRequirements imageMemoryRequirements = image.getMemoryRequirements();
        return AllocateDeviceMemory(device, imageMemoryRequirements.size, memoryTypeIndex, &dedicatedMemoryAllocateInfo);
    }

    VulkanDeviceMemory AllocateDedicatedBufferMemory(const vk::raii::Device &device, const vk::raii::Buffer& buffer,
        uint32_t memoryTypeIndex) {
        VkMemoryDedicatedAllocateInfo dedicatedMemoryAllocateInfo;
        dedicatedMemoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO;
        dedicatedMemoryAllocateInfo.buffer = *buffer;
        vk::MemoryRequirements bufferMemoryRequirements = buffer.getMemoryRequirements();
        return AllocateDeviceMemory(device, bufferMemoryRequirements.size, memoryTypeIndex, &dedicatedMemoryAllocateInfo);
    }
}
