#pragma once
#include "DependencyInstallerBase.h"

class RenderHardwareModuleInstaller : public DependencyInstallerBase<RenderHardwareModuleInstaller> {
public:
    void InstallBindings(DiContainer *diContainer) const override;
};
