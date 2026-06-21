#pragma once

#include "IRenderer.h"
#include "RendererType.h"

class IRendererFactory {
public:
    [[nodiscard]] virtual IRenderer* CreateRenderer(RendererType rendererType) = 0;
    virtual ~IRendererFactory() = default;
};
