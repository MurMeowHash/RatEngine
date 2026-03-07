#pragma once

#include "DependencyInstallerBase.h"

class DebugModuleInstaller : public DependencyInstallerBase<DebugModuleInstaller> {
public:
    void InstallBindings(DiContainer* diContainer) const override;
};