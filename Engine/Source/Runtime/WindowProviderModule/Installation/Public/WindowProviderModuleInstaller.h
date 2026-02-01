#pragma once

#include "DependencyInstallerBase.h"

class WindowProviderModuleInstaller : public DependencyInstallerBase<WindowProviderModuleInstaller> {
public:
    void InstallBindings(DiContainer &diContainer) const override;
};