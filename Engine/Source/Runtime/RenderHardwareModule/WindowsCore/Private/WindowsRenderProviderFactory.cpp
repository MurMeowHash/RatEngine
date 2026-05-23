#include "../Public/WindowsRenderProviderFactory.h"
#include "VulkanRenderProvider.h"
#include "ProjectSettings/ProjectSettings.h"
#include "Application/Application.h"
#include "BuildSettings/BuildSettings.h"

WindowsRenderProviderFactory::WindowsRenderProviderFactory(const DiContainer* diContainer)
: m_diContainer(diContainer) { }

std::unique_ptr<IRenderProvider> WindowsRenderProviderFactory::CreateRenderProvider(RenderingApi renderingApi) {
    switch (renderingApi) {
        case RenderingApi::Vulkan:
            return std::make_unique<VulkanRenderProvider>(
                    m_diContainer->Resolve<ProjectSettings>(),
                    m_diContainer->Resolve<Application>(),
                    m_diContainer->Resolve<BuildSettings>(),
                    m_diContainer); // TODO: instantiate via diContainer
        default:
            return nullptr; // TODO: throw exception instead
    }
}
