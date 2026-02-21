#include "../Public/VulkanRenderProvider.h"
#include "ProjectSettings/ProjectSettings.h"
#include "Application/Application.h"
#include "BuildSettings/BuildSettings.h"
#include "CoreUtils.h"

using Rat::Core::Flags::operator|=;

VulkanRenderProvider::VulkanRenderProvider(ProjectSettings *projectSettings, Application* application, BuildSettings* buildSettings,
                                           const DiContainer* diContainer)
: m_projectSettings(projectSettings), m_application(application), m_buildSettings(buildSettings),
m_diContainer(diContainer) {
    m_vulkanDependencyContext = new VulkanDependencyContext(m_diContainer);
}

Rat::RenderProviderModule::ExecResult VulkanRenderProvider::Initialize() {
    m_vulkanDependencyContext->OpenContext();
    AcquireInternalDependencies();

    Rat::RenderProviderModule::ExecResult execResult = CreateVulkanInstance();
    if(!CanContinueExecution(execResult))
        return execResult;

    if(m_buildSettings->GetIsDevelopmentBuild())
        execResult = InitializeVulkanDebug();

    return execResult;
}

void VulkanRenderProvider::Shutdown() {
    m_vulkanDependencyContext->CloseContext();
}

Rat::RenderProviderModule::ExecResult VulkanRenderProvider::CreateVulkanInstance() {
    GeneralSettings appGeneralSettings = m_projectSettings->GetGeneralSettings();
    ApplicationVersion engineVersion = m_application->GetEngineVersion();
    VulkanApiVersion minVulkanApiVersion = m_application->GetMinSupportedVulkanVersion();
    RenderingSettings renderingSettings = m_projectSettings->GetRenderingSettings();
    uint32_t minVulkanVersion = VK_MAKE_API_VERSION(minVulkanApiVersion.m_versionVariant,
                                                    minVulkanApiVersion.m_versionMajor,
                                                    minVulkanApiVersion.m_versionMinor,
                                                    minVulkanApiVersion.m_versionPatch);

    m_apiVersion = std::max(minVulkanVersion, m_vulkanContext.enumerateInstanceVersion().value);

    vk::ApplicationInfo appInfo;
    appInfo.pApplicationName = appGeneralSettings.m_projectTitle;
    appInfo.applicationVersion = VK_MAKE_VERSION(appGeneralSettings.m_versionMajor,
                                                 appGeneralSettings.m_versionMinor,
                                                 appGeneralSettings.m_versionPatch);
    appInfo.pEngineName = m_application->GetEngineName();
    appInfo.engineVersion = VK_MAKE_VERSION(engineVersion.m_engineVersionMajor,
                                            engineVersion.m_engineVersionMinor,
                                            engineVersion.m_engineVersionPatch);
    appInfo.apiVersion = m_apiVersion;

    vk::InstanceCreateInfo instanceInfo;
    instanceInfo.pApplicationInfo = &appInfo;
    Rat::RenderProviderModule::Vulkan::ExtensionAssembleFlags extensionAssembleFlags = Rat::RenderProviderModule::Vulkan::ExtensionAssembleFlags::None;
    if(m_buildSettings->GetIsDevelopmentBuild())
        extensionAssembleFlags |= Rat::RenderProviderModule::Vulkan::ExtensionAssembleFlags::IncludeDebug;

    std::vector<const char*> availableExtensions = m_vulkanExtensionsAssembler->GetAvailableInstanceExtensions(m_vulkanContext, extensionAssembleFlags);
    instanceInfo.enabledExtensionCount = availableExtensions.size();
    instanceInfo.ppEnabledExtensionNames = availableExtensions.data();
    std::vector<const char*> availableLayers = m_vulkanLayersValidator->ValidateLayers(m_vulkanContext,
                                                                                       renderingSettings.m_vulkanRenderingSettings.m_validationLayersNames);
    instanceInfo.enabledLayerCount = availableLayers.size();
    instanceInfo.ppEnabledLayerNames = availableLayers.data();

    Rat::RenderProviderModule::ExecResult instanceCreationResult = Rat::RenderProviderModule::ExecResult::Success;

    vk::ResultValue<vk::raii::Instance> instanceWrapper = m_vulkanContext.createInstance(instanceInfo);
    if(instanceWrapper.result == vk::Result::eErrorLayerNotPresent) {
        instanceInfo.enabledLayerCount = 0;
        instanceWrapper = m_vulkanContext.createInstance(instanceInfo);
        instanceCreationResult = Rat::RenderProviderModule::ExecResult::DebugCreationFailed;
    }

    if(instanceWrapper.result == vk::Result::eErrorIncompatibleDriver)
        return Rat::RenderProviderModule::ExecResult::IncompatibleDriver;

    if(instanceWrapper.result != vk::Result::eSuccess)
        return Rat::RenderProviderModule::ExecResult::UnknownFailure;

    m_vulkanInstance = std::move(instanceWrapper.value);
    return instanceCreationResult;
}

uint32_t VulkanRenderProvider::GetApiVersion() const {
    return m_apiVersion;
}

bool VulkanRenderProvider::CanContinueExecution(const Rat::RenderProviderModule::ExecResult &execResult) const {
    return execResult == Rat::RenderProviderModule::ExecResult::Success || execResult == Rat::RenderProviderModule::ExecResult::DebugCreationFailed;
}

Rat::RenderProviderModule::ExecResult VulkanRenderProvider::InitializeVulkanDebug() {
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
            m_vulkanInstance.createDebugUtilsMessengerEXT(debugUtilsMessengerCreateInfoEXT);

    if(debugMessangerWrapper.result != vk::Result::eSuccess)
        return Rat::RenderProviderModule::ExecResult::DebugCreationFailed;

    m_vulkanDebugMessanger = std::move(debugMessangerWrapper.value);
    return Rat::RenderProviderModule::ExecResult::Success;
}

void VulkanRenderProvider::AcquireInternalDependencies() {
    const DiContainer* diContainer = m_vulkanDependencyContext->GetContainer();
    m_vulkanExtensionsAssembler = diContainer->Resolve<IVulkanExtensionsAssembler>();
    m_vulkanLayersValidator = diContainer->Resolve<IVulkanLayersValidator>();
    m_vulkanDebugAdapter = diContainer->Resolve<IVulkanDebugAdapter>();
    m_vulkanDeviceProvider = diContainer->Resolve<IVulkanDeviceProvider>();
}

VulkanRenderProvider::~VulkanRenderProvider() {
    delete m_vulkanDependencyContext;
}