#pragma once

#include "IRenderHardwareProvider.h"
#include "RenderingApi.h"

struct RenderHardwareRuntimeData {
    IRenderHardwareProvider* m_renderHardwareProvider;
    RenderingApi m_usedRenderingApi;
};
