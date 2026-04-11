#pragma once

#include "StaticDelegate.h"

class ILogger;
class IPlatformInteractor;

class RenderCommand : public StaticDelegate<ILogger*, IPlatformInteractor*> {
public:
    explicit RenderCommand(const Internal::FunctionHandler &functionHandler)
    : StaticDelegate(functionHandler) {}
};