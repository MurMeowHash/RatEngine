#pragma once

#include "DependencyContextBase.h"

class EngineDependencyContext : public DependencyContextBase {
public:
    explicit EngineDependencyContext(const DiContainer* parentContainer = nullptr);
protected:
    void ConstructCompositionRoot() override;
};