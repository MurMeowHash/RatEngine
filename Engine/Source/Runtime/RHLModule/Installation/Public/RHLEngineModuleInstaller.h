#pragma once

#include "DependencyInstallerBase.h"

class RHLEngineModuleInstaller : public DependencyInstallerBase<RHLEngineModuleInstaller> {
public:
    void InstallBindings(DiContainer* diContainer) const override;
};