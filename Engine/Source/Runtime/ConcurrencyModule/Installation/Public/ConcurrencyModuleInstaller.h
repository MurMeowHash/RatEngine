#pragma once

#include "DependencyInstallerBase.h"

class ConcurrencyModuleInstaller : public DependencyInstallerBase<ConcurrencyModuleInstaller> {
public:
    void InstallBindings(DiContainer *diContainer) const override;
};