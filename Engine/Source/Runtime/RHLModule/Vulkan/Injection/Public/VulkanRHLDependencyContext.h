#pragma once

#include "RHLDependencyContext.h"

class VulkanRHLDependencyContext : public RHLDependencyContext {
public:
    explicit VulkanRHLDependencyContext(const DiContainer* parentDiContainer);
protected:
    void ConstructRHLDependencies() override;
};
