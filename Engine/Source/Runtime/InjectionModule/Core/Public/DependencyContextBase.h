#pragma once

#include "DiContainer.h"
#include "IDependencyContext.h"

class DependencyContextBase : public IDependencyContext {
public:
    explicit DependencyContextBase(const DiContainer* parentContainer = nullptr);
    void OpenContext() override;
    void CloseContext() override;

    [[nodiscard]] const DiContainer* GetContainer() const override;

    ~DependencyContextBase() override;
protected:
    DiContainer* m_diContainer;

    virtual void ConstructCompositionRoot() = 0;
};