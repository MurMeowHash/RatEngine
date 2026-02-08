#pragma once

#include "DependencyInstallerBase.h"

class VulkanRenderModuleInstaller : public DependencyInstallerBase<VulkanRenderModuleInstaller> {
public:
    void InstallBindings(DiContainer &diContainer) const override;
};