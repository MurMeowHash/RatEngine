#pragma once

#include "DependencyInstallerBase.h"

class VulkanHardwareInstaller : public DependencyInstallerBase<VulkanHardwareInstaller> {
public:
    void InstallBindings(DiContainer* diContainer) const override;
};