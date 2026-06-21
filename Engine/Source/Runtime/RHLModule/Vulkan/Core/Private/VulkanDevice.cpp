#include "VulkanDevice.h"
#include "Memory/VulkanDeviceMemoryProvider.h"

bool VulkanDevice::TryGetAvailableExtensions(std::vector<vk::ExtensionProperties> &availableExtensions) const {
    vk::ResultValue<std::vector<vk::ExtensionProperties>> supportedDeviceExtensions = m_physicalDevice.enumerateDeviceExtensionProperties();
    if (supportedDeviceExtensions.result != vk::Result::eSuccess)
        return false;

    availableExtensions = supportedDeviceExtensions.value;
    return true;
}

VulkanDevice::VulkanDevice(IVulkanExtensionsValidator* vulkanExtensionsValidator, IVulkanDeviceFeaturesAssembler* vulkanDeviceFeaturesAssembler,
    IVulkanDeviceMemoryProviderFactory* vulkanDeviceMemoryProviderFactory)
: VulkanEntity(vulkanExtensionsValidator), m_vulkanDeviceFeaturesAssembler(vulkanDeviceFeaturesAssembler),
m_vulkanDeviceMemoryProviderFactory(vulkanDeviceMemoryProviderFactory) { }

VulkanDevice::~VulkanDevice() {
    delete m_memoryProvider;
}

bool VulkanDevice::Initialize(const VulkanDeviceInitializationInfo& initializationInfo) {
    m_physicalDevice = initializationInfo.m_physicalDevice;
    SetApiVersion(m_physicalDevice.getProperties2().properties.apiVersion);

    std::vector<vk::DeviceQueueCreateInfo> queuesCreateInfos = InitializeDeviceQueues(initializationInfo.m_requestedQueues);
    ProcessExtensionsRequest(initializationInfo.m_requestedExtensions);
    VulkanDeviceFeaturesAssembleData featuresAssembleData =
        m_vulkanDeviceFeaturesAssembler->AssembleDeviceFeatures(m_physicalDevice, initializationInfo.m_requestedFeatures);

    vk::DeviceCreateInfo deviceCreateInfo;
    deviceCreateInfo.queueCreateInfoCount = queuesCreateInfos.size();
    deviceCreateInfo.pQueueCreateInfos = queuesCreateInfos.data();
    std::vector<const char*> extensions = GetSupportedExtensionNames();
    deviceCreateInfo.enabledExtensionCount = extensions.size();
    deviceCreateInfo.ppEnabledExtensionNames = extensions.data();
    deviceCreateInfo.pNext = &featuresAssembleData.m_featuresChain;

    vk::ResultValue<vk::raii::Device> deviceWrapper = m_physicalDevice.createDevice(deviceCreateInfo);
    if(deviceWrapper.result != vk::Result::eSuccess)
        return false;

    m_features = featuresAssembleData.m_queryResult;

    m_device = std::move(deviceWrapper.value);
    ObtainQueues();
    InitializeMemoryProvider(initializationInfo.m_memoryProviderType);
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

vk::raii::Device & VulkanDevice::GetHandle() {
    return m_device;
}

IVulkanDeviceMemoryProvider* VulkanDevice::GetMemoryProvider() {
    return m_memoryProvider;
}

std::vector<VulkanQueueData> VulkanDevice::GetOperatingQueues() const {
    std::vector<VulkanQueueData> queues;
    queues.reserve(m_deviceQueues.size());
    for (const std::pair<const vk::QueueFlagBits, VulkanQueueData>& queue : m_deviceQueues) {
        queues.emplace_back(queue.second);
    }

    return queues;
}

bool VulkanDevice::TryGetQueue(vk::QueueFlagBits queueFlagBits, VulkanQueueData &outQueueData) const {
    auto queueIterator = m_deviceQueues.find(queueFlagBits);
    if (queueIterator == m_deviceQueues.end())
        return false;

    outQueueData = queueIterator->second;
    return true;
}

void VulkanDevice::ObtainQueues() {
    for(std::pair<const vk::QueueFlagBits, VulkanQueueData> &deviceQueue : m_deviceQueues) {
        deviceQueue.second.m_queue = m_device.getQueue(deviceQueue.second.m_queueIndex, 0);
    }
}

void VulkanDevice::InitializeMemoryProvider(VulkanMemoryProviderType memoryProviderType) {
    m_memoryProvider = m_vulkanDeviceMemoryProviderFactory->CreateVulkanDeviceMemoryProvider(memoryProviderType,
        m_device, m_physicalDevice);
}