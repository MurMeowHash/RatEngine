#pragma once

#include "DependencyContextBase.h"

class EngineDependencyContext : public DependencyContextBase {
protected:
    void ConstructCompositionRoot() override;
};