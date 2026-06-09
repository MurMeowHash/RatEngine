#pragma once

#include <memory>

class IEngineLoop;

namespace Rat::EngineLoops {
    extern std::shared_ptr<IEngineLoop> g_coreLoop;
    extern std::shared_ptr<IEngineLoop> g_renderHardwareLoop;
}
