#pragma once
#include "DependencyInstallerBase.h"

class RHLModuleInstaller : public DependencyInstallerBase<RHLModuleInstaller> {
public:
    void InstallBindings(DiContainer *diContainer) const override;
};
