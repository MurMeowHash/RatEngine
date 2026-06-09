#pragma once

#include "DependencyContextBase.h"

enum class RenderingApi;

class RenderHardwareDependencyContext : public DependencyContextBase {
public:
    explicit RenderHardwareDependencyContext(const DiContainer* parentContainer = nullptr);
protected:
    void ConstructCompositionRoot() override;
    virtual void ConstructRenderHardwareDependencies() = 0;
};
