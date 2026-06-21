#include "../Public/WindowsRHLDependencyContextFactory.h"
#include "RenderingApi.h"
#include "VulkanRHLDependencyContext.h"
#include <stdexcept>
#include "CoreUtils.h"
#include "DiContainer.h"

RHLDependencyContext* WindowsRHLDependencyContextFactory::CreateRHLDependencyContext(RenderingApi renderingApi, DiContainer* parentDiContainer) {
    switch (renderingApi) {
        case RenderingApi::Vulkan:
            return new VulkanRHLDependencyContext(parentDiContainer);
        default:
            throw std::invalid_argument(StringFormatter("Rendering api ", static_cast<uint32_t>(renderingApi), " is not supported for Windows"));
    }
}
