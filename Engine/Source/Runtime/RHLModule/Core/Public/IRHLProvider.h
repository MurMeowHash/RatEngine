#pragma once

#include "Resources/IRHLTexture.h"
#include "Resources/RHLTextureGlobals.h"

class IRHLProvider {
public:
    [[nodiscard]] virtual bool Initialize() = 0;
    virtual void Shutdown() = 0;
    virtual IRHLTexture* CreateTexture(const RHLTextureCreateInfo& createInfo) = 0;
    virtual ~IRHLProvider() = default;
};