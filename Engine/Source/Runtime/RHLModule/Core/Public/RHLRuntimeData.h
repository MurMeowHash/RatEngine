#pragma once

#include "IRHLProvider.h"
#include "RenderingApi.h"

struct RHLRuntimeData {
    IRHLProvider* m_rhlProvider;
    RenderingApi m_usedRenderingApi;
};
