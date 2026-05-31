#pragma once

#include <vulkan/vulkan.hpp>

struct VulkanDeviceMemoryInitializer {
    vk::DeviceMemory m_handle;
    vk::DeviceSize m_offset;
    vk::DeviceSize m_alignmentOffset;
    uint32_t m_size;
    uint32_t m_memoryTypeIndex;
};

class VulkanDeviceMemory {
public:
    explicit VulkanDeviceMemory();
    VulkanDeviceMemory(const VulkanDeviceMemoryInitializer& memoryInitializer);

    void InitializeMemory(const VulkanDeviceMemoryInitializer& memoryInitializer);

    [[nodiscard]] uint32_t GetSize() const;
    [[nodiscard]] uint32_t GetAllocationSize() const;
    [[nodiscard]] uint32_t GetMemoryTypeIndex() const;
    [[nodiscard]] vk::DeviceMemory GetHandle() const;
    [[nodiscard]] uint32_t GetOffset() const;
    [[nodiscard]] vk::DeviceSize GetAlignmentOffset() const;
    [[nodiscard]] vk::DeviceSize GetMemoryOccupationOffset() const;
    [[nodiscard]] bool IsValid() const;

private:
    vk::DeviceMemory m_handle;
    vk::DeviceSize m_offset;
    vk::DeviceSize m_alignmentOffset;
    uint32_t m_size;
    uint32_t m_memoryTypeIndex;
};