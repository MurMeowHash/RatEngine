#pragma once

#include "DiContainer.h"
#include "IDependencyContext.h"

class DependencyContextBase : public IDependencyContext {
public:
    void OpenContext() override;
    void CloseContext() override;

    const DiContainer &GetContainer() const override {
        return m_diContainer;
    }
protected:
    DiContainer m_diContainer;

    virtual void ConstructCompositionRoot() = 0;
};