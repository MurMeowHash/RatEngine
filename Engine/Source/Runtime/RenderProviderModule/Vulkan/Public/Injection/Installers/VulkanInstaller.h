#pragma once

#include "DependencyInstallerBase.h"

class VulkanInstaller : public DependencyInstallerBase<VulkanInstaller> {
public:
    void InstallBindings(DiContainer* diContainer) const override;
};