#pragma once

#include <vector>
#include "RenderingApi.h"

struct RenderApiPriorityConfiguration {
    explicit RenderApiPriorityConfiguration() {
        m_renderApiPriorityQueue = {
            RenderingApi::None
        };
    }

    std::vector<RenderingApi> m_renderApiPriorityQueue;
};

struct WindowsRenderApiPriorityConfiguration : public RenderApiPriorityConfiguration {
    explicit WindowsRenderApiPriorityConfiguration() {
        m_renderApiPriorityQueue = {
            RenderingApi::Vulkan
        };
    }
};
