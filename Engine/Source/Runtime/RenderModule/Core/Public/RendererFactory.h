#pragma once
#include "IRendererFactory.h"

class DiContainer;

class RendererFactory : public IRendererFactory {
public:
    explicit RendererFactory(DiContainer* diContainer);
    [[nodiscard]] IRenderer* CreateRenderer(RendererType rendererType) override;
private:
    DiContainer* m_diContainer;
};
