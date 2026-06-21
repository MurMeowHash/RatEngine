#pragma once

#include <cstdint>
#include "Vectors/Vector2D.h"

enum class RHLTextureType {
    None = 0,
    Texture2D = 1,
};

enum class RHLPixelFormat {
    None = 0,
    R8G8B8 = 1,
};

enum class RHLTextureCreateFlags : uint32_t {
    None = 0,
    CPUReadback = 1 << 0,
    RenderTarget = 1 << 1,
    DepthStencilTarget = 1 << 2,
};

struct RHLTextureCreateInfo {
    RHLTextureCreateFlags m_createFlags;
    RHLTextureType m_type;
    RHLPixelFormat m_pixelFormat;
    Vector2D<uint32_t> m_extents;
    uint32_t m_depth;
    uint32_t m_mipsCount;
    uint32_t m_arraySize;
    uint32_t m_sampleCount;
};