#pragma once
#include "DependencyInstallerBase.h"

class VulkanConfigurationsInstaller : public DependencyInstallerBase<VulkanConfigurationsInstaller> {
public:
    void InstallBindings(DiContainer *diContainer) const override;
};
