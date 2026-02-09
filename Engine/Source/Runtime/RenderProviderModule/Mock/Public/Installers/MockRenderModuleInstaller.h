#pragma once

#include "DependencyInstallerBase.h"

class MockRenderModuleInstaller : public DependencyInstallerBase<MockRenderModuleInstaller> {
public:
    void InstallBindings(DiContainer &diContainer) const override {}
};