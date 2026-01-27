#include "../Public/DependencyContextBase.h"

void DependencyContextBase::OpenContext() {
    ConstructCompositionRoot();
    m_diContainer.ResolveDependencies();
}

void DependencyContextBase::CloseContext() {
    m_diContainer.Destroy();
}