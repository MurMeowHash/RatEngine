#include "../Public/MockRHLDependencyContext.h"

MockRHLDependencyContext::MockRHLDependencyContext(const DiContainer *parentDiContainer)
: RHLDependencyContext(parentDiContainer) { }

void MockRHLDependencyContext::ConstructRHLDependencies() { }
