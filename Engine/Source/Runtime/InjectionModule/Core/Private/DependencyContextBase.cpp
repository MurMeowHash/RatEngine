#include "../Public/DependencyContextBase.h"

DependencyContextBase::DependencyContextBase(const DiContainer *parentContainer) {
    m_diContainer = new DiContainer(parentContainer);
}

void DependencyContextBase::OpenContext() {
    ConstructCompositionRoot();
    m_diContainer->ResolveDependencies();
}

void DependencyContextBase::CloseContext() {
    m_diContainer->Destroy();
}

const DiContainer * DependencyContextBase::GetContainer() const {
    return m_diContainer;
}

DependencyContextBase::~DependencyContextBase() {
    delete m_diContainer;
}