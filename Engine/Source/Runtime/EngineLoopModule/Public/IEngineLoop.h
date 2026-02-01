#pragma once

#include "CoreGlobals.h"

class IEngineLoop {
public:
    virtual Rat::Core::ErrorSeverity Initialize() = 0;
    virtual Rat::Core::ErrorSeverity Tick() = 0;
    virtual Rat::Core::ErrorSeverity Exit() = 0;
    virtual ~IEngineLoop() = default;
};