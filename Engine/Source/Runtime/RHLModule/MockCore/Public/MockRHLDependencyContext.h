#pragma once

#include "RHLDependencyContext.h"

class MockRHLDependencyContext : public RHLDependencyContext {
public:
    explicit MockRHLDependencyContext(const DiContainer* parentDiContainer);
protected:
    void ConstructRHLDependencies() override;
};
