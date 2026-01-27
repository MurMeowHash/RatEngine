#pragma once

#include "IDependencyInstaller.h"

template<typename TInstaller>
class DependencyInstallerBase : IDependencyInstaller {
public:
    static void InstallDependencies(DiContainer &diContainer) {
        TInstaller installerInstance;
        installerInstance.InstallBindings(diContainer);
    }
};