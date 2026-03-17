#include "../Public/MockRenderPriorityQueue.h"

std::vector<RenderingApi> MockRenderPriorityQueue::GetRenderingApiQueue() const {
    return std::vector<RenderingApi> { RenderingApi::None };
}