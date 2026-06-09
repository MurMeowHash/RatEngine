#pragma once

#include "../../../Installation/Public/RenderHardwareDependencyContext.h"

class VulkanRenderHardwareDependencyContext : public RenderHardwareDependencyContext {
public:
    explicit VulkanRenderHardwareDependencyContext(const DiContainer* parentDiContainer);
protected:
    void ConstructRenderHardwareDependencies() override;
};
