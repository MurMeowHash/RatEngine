#pragma once

#include "RenderHardwareDependencyContext.h"

class MockRenderHardwareDependencyContext : public RenderHardwareDependencyContext {
public:
    explicit MockRenderHardwareDependencyContext(const DiContainer* parentDiContainer);
protected:
    void ConstructRenderHardwareDependencies() override;
};
