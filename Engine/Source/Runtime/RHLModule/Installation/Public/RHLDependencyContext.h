#pragma once

#include "DependencyContextBase.h"

enum class RenderingApi;

class RHLDependencyContext : public DependencyContextBase {
public:
    explicit RHLDependencyContext(const DiContainer* parentContainer = nullptr);
protected:
    void ConstructCompositionRoot() override;
    virtual void ConstructRHLDependencies() = 0;
};
