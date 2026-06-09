#include "EngineLoopGlobals.h"
#include "CoreLoop.h"
#include "RenderHardwareLoop.h"

namespace Rat::EngineLoops {
    std::shared_ptr<IEngineLoop> g_coreLoop = std::make_shared<CoreLoop>();
    std::shared_ptr<IEngineLoop> g_renderHardwareLoop = nullptr;
}