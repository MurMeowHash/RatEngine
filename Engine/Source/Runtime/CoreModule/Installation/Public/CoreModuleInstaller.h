#pragma once

#include "DependencyInstallerBase.h"

class CoreModuleInstaller : public DependencyInstallerBase<CoreModuleInstaller> {
public:
    void InstallBindings(DiContainer* diContainer) const override;
};