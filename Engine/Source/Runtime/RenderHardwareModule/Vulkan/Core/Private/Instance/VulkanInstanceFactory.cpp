#include "../../Public/Instance/VulkanInstanceFactory.h"
#include "DiContainer.h"
#include "ProjectSettings/ProjectSettings.h"
#include "Application/Application.h"

VulkanInstanceFactory::VulkanInstanceFactory(DiContainer *diContainer, VulkanInstanceConfiguration* vulkanInstanceConfiguration,
        VulkanExtensionsConfiguration* vulkanExtensionsConfiguration)
: m_diContainer(diContainer), m_vulkanInstanceConfiguration(vulkanInstanceConfiguration),
m_vulkanExtensionsConfiguration(vulkanExtensionsConfiguration) { }

VulkanInstance* VulkanInstanceFactory::CreateVulkanInstance(const VulkanInstanceInitializationInfo &initializationInfo,
    bool* initializationSucceeded) {
    VulkanInstance* vulkanInstance = m_diContainer->Instantiate<VulkanInstance>().WithArguments<IVulkanExtensionsValidator,
    IVulkanLayersValidator, IVulkanDebugAdapter, ProjectSettings, Application>();
    bool initialized = vulkanInstance->Initialize(initializationInfo);
    if(initializationSucceeded != nullptr)
        *initializationSucceeded = initialized;

    return vulkanInstance;
}

VulkanInstance* VulkanInstanceFactory::CreateVulkanInstance(InstanceCreationFlags creationFlags, bool *initializationSucceeded) {
    VulkanInstanceInitializationInfo initializationInfo;
    initializationInfo.m_requestedExtensions = m_vulkanExtensionsConfiguration->m_instanceExtensions;
    initializationInfo.m_requestedLayers = m_vulkanInstanceConfiguration->m_validationLayersNames;
    initializationInfo.m_minVulkanVersion = m_vulkanInstanceConfiguration->m_minVulkanVersion;
    initializationInfo.m_creationFlags = creationFlags;
    return CreateVulkanInstance(initializationInfo, initializationSucceeded);
}