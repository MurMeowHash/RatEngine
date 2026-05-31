#include "VulkanDevice.h"

VulkanDevice::VulkanDevice(IDeviceFeaturesAssembler *deviceFeaturesAssembler)
: m_deviceFeaturesAssembler(deviceFeaturesAssembler) { }

bool VulkanDevice::Initialize(const vk::raii::PhysicalDevice& physicalDevice, vk::QueueFlags requestedQueues,
                              const std::vector<VulkanExtension> &requestedExtensions) {
    m_physicalDevice = physicalDevice;
    m_apiVersion = m_physicalDevice.getProperties2().properties.apiVersion;

    std::vector<vk::DeviceQueueCreateInfo> queuesCreateInfos = InitializeDeviceQueues(requestedQueues);
    FilterExtensions(requestedExtensions);
    DeviceFeaturesAssembleData assembleData = InitializeDeviceFeatures();

    vk::DeviceCreateInfo deviceCreateInfo;
    deviceCreateInfo.queueCreateInfoCount = queuesCreateInfos.size();
    deviceCreateInfo.pQueueCreateInfos = queuesCreateInfos.data();
    std::vector<const char*> extensions = GetRequiredOrSupportedExtensionNames();
    deviceCreateInfo.enabledExtensionCount = extensions.size();
    deviceCreateInfo.ppEnabledExtensionNames = extensions.data();
    deviceCreateInfo.pNext = &assembleData.m_featuresChain;

    vk::ResultValue<vk::raii::Device> deviceWrapper = m_physicalDevice.createDevice(deviceCreateInfo);
    if(deviceWrapper.result != vk::Result::eSuccess)
        return false;

    m_device = std::move(deviceWrapper.value);
    ObtainQueues();
    InitializeMemoryProperties();
    return true;
}

std::vector<vk::DeviceQueueCreateInfo> VulkanDevice::InitializeDeviceQueues(vk::QueueFlags requestedQueues) {
    m_deviceQueues.clear();

    std::vector<vk::QueueFamilyProperties2> deviceQueueFamilies = m_physicalDevice.getQueueFamilyProperties2();
    std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;

    while(requestedQueues) {
        vk::QueueFlags::MaskType rawQueueFlags = static_cast<vk::QueueFlags::MaskType>(requestedQueues);
        vk::QueueFlags::MaskType lowestRawQueueFlag = rawQueueFlags & (~rawQueueFlags + 1);
        vk::QueueFlagBits inspectedQueueBit = static_cast<vk::QueueFlagBits>(lowestRawQueueFlag);
        requestedQueues &= ~vk::QueueFlags(inspectedQueueBit);

        for(size_t i = 0; i < deviceQueueFamilies.size(); i++) {
            if(deviceQueueFamilies[i].queueFamilyProperties.queueFlags & inspectedQueueBit) {
                m_deviceQueues[inspectedQueueBit] = VulkanQueueData(i, nullptr);
                const float queuePriority = 1.0f;
                vk::DeviceQueueCreateInfo queueCreateInfo({}, i, 1, &queuePriority);
                queueCreateInfos.emplace_back(queueCreateInfo);
                break;
            }
        }
    }

    return queueCreateInfos;
}

void VulkanDevice::FilterExtensions(const std::vector<VulkanExtension> &requestedExtensions) {
    m_extensions.clear();
    vk::ResultValueType<std::vector<vk::ExtensionProperties>>::type availableExtensions = m_physicalDevice.enumerateDeviceExtensionProperties();
    for(const VulkanExtension& requestedExtension : requestedExtensions) {
        auto extensionIterator = m_extensions.emplace(requestedExtension.GetExtensionEncoding(), requestedExtension);

        if(std::ranges::any_of(availableExtensions.value, [&requestedExtension](const vk::ExtensionProperties& availableExtension){
            return std::strcmp(requestedExtension.GetExtensionName(), availableExtension.extensionName) == 0;
        }))
            extensionIterator.first->second.MarkSupported();
        else
            extensionIterator.first->second.MarkUnsupported();
    }
}

bool VulkanDevice::IsExtensionSupported(const char *extensionName) const {
    return IsExtensionSupported(VulkanExtension::EncodeExtensionName(extensionName));
}

bool VulkanDevice::IsExtensionSupported(VulkanExtension::EncodingType extensionEncoding) const {
    auto extensionIterator = m_extensions.find(extensionEncoding);
    if(extensionIterator == m_extensions.end())
        return false;

    return extensionIterator->second.IsSupported();
}

uint32_t VulkanDevice::GetApiVersion() const {
    return m_apiVersion;
}

vk::PhysicalDeviceMemoryProperties VulkanDevice::GetDeviceMemoryProperties() const {
    return m_deviceMemoryProperties;
}

vk::raii::Device & VulkanDevice::GetInternalDevice() {
    return m_device;
}

std::vector<const char *> VulkanDevice::GetRequiredOrSupportedExtensionNames() const {
    std::vector<const char*> mandatoryExtensionNames;
    mandatoryExtensionNames.reserve(m_extensions.size());

    for(const std::pair<const VulkanExtension::EncodingType, VulkanExtension>& extensionUnit : m_extensions) {
        if(extensionUnit.second.IsSupported() || extensionUnit.second.IsRequired())
            mandatoryExtensionNames.emplace_back(extensionUnit.second.GetExtensionName());
    }

    return mandatoryExtensionNames;
}

DeviceFeaturesAssembleData VulkanDevice::InitializeDeviceFeatures() {
    DeviceFeaturesAssembleData assembleData = m_deviceFeaturesAssembler->AssembleDeviceFeatures(m_physicalDevice, m_apiVersion);
    m_features = assembleData.m_queryResult;
    return assembleData;
}

void VulkanDevice::ObtainQueues() {
    for(std::pair<const vk::QueueFlagBits, VulkanQueueData> &deviceQueue : m_deviceQueues) {
        deviceQueue.second.m_queue = m_device.getQueue(deviceQueue.second.m_queueIndex, 0);
    }
}

void VulkanDevice::InitializeMemoryProperties() {
    m_deviceMemoryProperties = m_physicalDevice.getMemoryProperties();
}