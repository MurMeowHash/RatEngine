#pragma once

#include "DependencyContextBase.h"

class VulkanDependencyContext : public DependencyContextBase {
protected:
    void ConstructCompositionRoot() override;
};