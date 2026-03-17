#pragma once

#include <memory>
#include "IRenderProvider.h"

struct RenderProviderAccessor {
    std::unique_ptr<IRenderProvider> m_renderProvider;
};