#include "../../Public/Instance/VulkanInstance.h"

#include "CoreGlobals.h"
#include "CoreUtils.h"
#include "RenderHardwareProviderExecResult.h"
#include "ProjectSettings/ProjectSettings.h"
#include "Application/Application.h"

bool VulkanInstance::TryGetAvailableExtensions(std::vector<vk::ExtensionProperties> &availableExtensions) const {
    vk::ResultValue<std::vector<vk::ExtensionProperties>> extensionsQueryResult = m_vulkanContext.enumerateInstanceExtensionProperties();
    if (extensionsQueryResult.result != vk::Result::eSuccess)
        return false;

    availableExtensions = extensionsQueryResult.value;
    return true;
}

VulkanInstance::VulkanInstance(IVulkanExtensionsValidator* vulkanExtensionValidator, IVulkanLayersValidator* vulkanLayersValidator,
    IVulkanDebugAdapter* vulkanDebugAdapter, ProjectSettings *projectSettings, Application *application)
: VulkanEntity(vulkanExtensionValidator), m_vulkanLayersValidator(vulkanLayersValidator), m_vulkanDebugAdapter(vulkanDebugAdapter),
m_projectSettings(projectSettings), m_application(application) { }

bool VulkanInstance::Initialize(const VulkanInstanceInitializationInfo& initializationInfo) {
    GeneralSettings appGeneralSettings = m_projectSettings->GetGeneralSettings();
    ApplicationVersion engineVersion = m_application->GetEngineVersion();
    uint32_t minVulkanVersion = initializationInfo.m_minVulkanVersion.ToVulkanVersion();

    SetApiVersion(std::max(minVulkanVersion, m_vulkanContext.enumerateInstanceVersion().value));

    vk::ApplicationInfo appInfo;
    appInfo.pApplicationName = appGeneralSettings.m_projectTitle;
    appInfo.applicationVersion = VK_MAKE_VERSION(appGeneralSettings.m_versionMajor,
                                                 appGeneralSettings.m_versionMinor,
                                                 appGeneralSettings.m_versionPatch);
    appInfo.pEngineName = m_application->GetEngineName();
    appInfo.engineVersion = VK_MAKE_VERSION(engineVersion.m_engineVersionMajor,
                                            engineVersion.m_engineVersionMinor,
                                            engineVersion.m_engineVersionPatch);
    appInfo.apiVersion = GetApiVersion();

    vk::InstanceCreateInfo instanceInfo;
    instanceInfo.pApplicationInfo = &appInfo;
    ProcessExtensionsRequest(initializationInfo.m_requestedExtensions);
    std::vector<const char*> queriedExtensions = GetSupportedExtensionNames();
    instanceInfo.enabledExtensionCount = queriedExtensions.size();
    instanceInfo.ppEnabledExtensionNames = queriedExtensions.data();
    uint32_t droppedLayersCount = 0;
    std::vector<const char*> availableLayers =
        m_vulkanLayersValidator->ValidateLayers(m_vulkanContext, initializationInfo.m_requestedLayers, droppedLayersCount);

    if (droppedLayersCount != 0 && !Rat::Core::Flags::IsFlagSet(initializationInfo.m_creationFlags, InstanceCreationFlags::AllowDropLayers))
        return false;

    instanceInfo.enabledLayerCount = availableLayers.size();
    instanceInfo.ppEnabledLayerNames = availableLayers.data();

    vk::ResultValue<vk::raii::Instance> instanceWrapper = m_vulkanContext.createInstance(instanceInfo);

    if (instanceWrapper.result != vk::Result::eSuccess)
        return false;

    m_handle = std::move(instanceWrapper.value);

    if (Rat::Core::Flags::IsFlagSet(initializationInfo.m_creationFlags, InstanceCreationFlags::UseDebug)) {
        bool vulkanDebugInitialized = InitializeVulkanDebug();
        if (!vulkanDebugInitialized && !Rat::Core::Flags::IsFlagSet(initializationInfo.m_creationFlags, InstanceCreationFlags::AllowDropDebug))
            return false;
    }

    return true;
}

vk::raii::Instance& VulkanInstance::GetHandle() {
    return m_handle;
}

bool VulkanInstance::InitializeVulkanDebug() {
    if (!IsExtensionSupported(vk::EXTDebugUtilsExtensionName))
        return false;

    vk::DebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCreateInfoEXT;
    debugUtilsMessengerCreateInfoEXT.messageSeverity =
            vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose |
            vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
            vk::DebugUtilsMessageSeverityFlagBitsEXT::eError;
    debugUtilsMessengerCreateInfoEXT.messageType =
            vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
            vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation |
            vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance;
    debugUtilsMessengerCreateInfoEXT.pfnUserCallback = m_vulkanDebugAdapter->GetVulkanDebugCallback();

    vk::ResultValue<vk::raii::DebugUtilsMessengerEXT> debugMessangerWrapper =
            m_handle.createDebugUtilsMessengerEXT(debugUtilsMessengerCreateInfoEXT);

    if(debugMessangerWrapper.result != vk::Result::eSuccess)
        return false;

    m_vulkanDebugMessanger = std::move(debugMessangerWrapper.value);
    return true;
}
