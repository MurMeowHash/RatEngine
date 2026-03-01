#include "WindowsRenderPriorityQueue.h"

std::vector<RenderingApi> WindowsRenderPriorityQueue::GetRenderingApiQueue() const {
    return std::vector<RenderingApi> { RenderingApi::Vulkan };
}