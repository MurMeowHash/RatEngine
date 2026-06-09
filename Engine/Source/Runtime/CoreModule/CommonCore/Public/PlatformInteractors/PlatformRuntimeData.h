#pragma once

enum class PlatformType {
    None = 0,
    Windows = 1,
};

enum class PlatformCategory {
    None = 0,
    Desktop = 1,
};

struct PlatformRuntimeData {
    PlatformType m_platformType;
    PlatformCategory m_platformCategory;
};