#pragma once

#include "DiContainer.h"

class IDependencyInstaller {
public:
    virtual void InstallBindings(DiContainer* diContainer) const = 0;
    virtual ~IDependencyInstaller() = default;
};