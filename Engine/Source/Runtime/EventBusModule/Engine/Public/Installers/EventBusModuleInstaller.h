#pragma once

#include "DependencyInstallerBase.h"

class EventBusModuleInstaller : public DependencyInstallerBase<EventBusModuleInstaller> {
public:
    void InstallBindings(DiContainer &diContainer) const override;
};