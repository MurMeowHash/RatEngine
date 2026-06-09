#pragma once

#include "DependencyInstallerBase.h"

class RenderHardwareEngineModuleInstaller : public DependencyInstallerBase<RenderHardwareEngineModuleInstaller> {
public:
    void InstallBindings(DiContainer* diContainer) const override;
};