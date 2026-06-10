#pragma once

#include "../../../Installation/Public/RHLDependencyContext.h"

class VulkanRHLDependencyContext : public RHLDependencyContext {
public:
    explicit VulkanRHLDependencyContext(const DiContainer* parentDiContainer);
protected:
    void ConstructRHLDependencies() override;
};
