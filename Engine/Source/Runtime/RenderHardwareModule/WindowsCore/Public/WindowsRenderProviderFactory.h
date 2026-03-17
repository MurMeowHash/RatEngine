#pragma once

#include "IRenderProviderFactory.h"
#include "DiContainer.h"

class WindowsRenderProviderFactory : public IRenderProviderFactory {
public:
    explicit WindowsRenderProviderFactory(const DiContainer* diContainer);
    std::unique_ptr<IRenderProvider> CreateRenderProvider(RenderingApi renderingApi) override;
private:
    const DiContainer* m_diContainer;
};