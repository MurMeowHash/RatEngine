#pragma once

#include "WindowCreateInfo.h"
#include "WindowProviderExecResult.h"

class IWindowProvider {
public:
    virtual Rat::WindowProviderModule::ExecResult CreateMainWindow(const WindowCreateInfo& windowCreateInfo) = 0;
    virtual void Tick() = 0;
    virtual void Shutdown() = 0;
    virtual ~IWindowProvider() = default;
};