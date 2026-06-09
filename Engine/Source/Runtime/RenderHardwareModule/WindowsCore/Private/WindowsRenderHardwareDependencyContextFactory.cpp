#include "../Public/WindowsRenderHardwareDependencyContextFactory.h"
#include "RenderingApi.h"
#include "VulkanRenderHardwareDependencyContext.h"
#include <stdexcept>
#include "CoreUtils.h"
#include "DiContainer.h"

RenderHardwareDependencyContext* WindowsRenderHardwareDependencyContextFactory::CreateRenderHardwareDependencyContext(RenderingApi renderingApi, DiContainer* parentDiContainer) {
    switch (renderingApi) {
        case RenderingApi::Vulkan:
            return new VulkanRenderHardwareDependencyContext(parentDiContainer);
        default:
            throw std::invalid_argument(StringFormatter("Rendering api ", static_cast<uint32_t>(renderingApi), " is not supported for Windows"));
    }
}
