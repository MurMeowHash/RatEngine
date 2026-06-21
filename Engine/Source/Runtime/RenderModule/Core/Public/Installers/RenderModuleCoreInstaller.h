#pragma once
#include "DependencyInstallerBase.h"

class RenderModuleCoreInstaller : public DependencyInstallerBase<RenderModuleCoreInstaller> {
public:
    void InstallBindings(DiContainer *diContainer) const override;
};
