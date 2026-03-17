#pragma once

#include "DependencyContextBase.h"

class VulkanDependencyContext : public DependencyContextBase {
public:
    explicit VulkanDependencyContext(const DiContainer* parentContainer = nullptr);
protected:
    void ConstructCompositionRoot() override;
};