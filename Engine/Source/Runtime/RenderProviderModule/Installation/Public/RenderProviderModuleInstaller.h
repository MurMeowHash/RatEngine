#pragma once

#include "DependencyInstallerBase.h"

class RenderProviderModuleInstaller : public DependencyInstallerBase<RenderProviderModuleInstaller> {
public:
    void InstallBindings(DiContainer &diContainer) const override;
};