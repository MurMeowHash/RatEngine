#pragma once

#include "StaticDelegate.h"

class RenderCommand : public StaticDelegate<> {
public:
    explicit RenderCommand(const Internal::FunctionHandler &functionHandler)
    : StaticDelegate(functionHandler) {}
};