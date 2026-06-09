#pragma once

#include <unordered_map>
#include "RenderApiPriorityConfiguration.h"
#include "PlatformInteractors/PlatformRuntimeData.h"

struct RenderApiConfiguration {
    explicit RenderApiConfiguration() {
        m_renderApiPriorityConfigurations = {
            {PlatformType::Windows, WindowsRenderApiPriorityConfiguration()}
        };
    }

    std::unordered_map<PlatformType, RenderApiPriorityConfiguration> m_renderApiPriorityConfigurations;
};
