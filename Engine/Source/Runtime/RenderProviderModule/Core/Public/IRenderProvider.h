#pragma once

#include <cstdint>
#include "RenderProviderExecResult.h"

class IRenderProvider {
public:
    virtual Rat::RenderProviderModule::ExecResult Initialize() = 0;
    [[nodiscard]] virtual uint32_t GetApiVersion() const = 0;
    [[nodiscard]] virtual bool CanContinueExecution(const Rat::RenderProviderModule::ExecResult& execResult) const = 0;
    virtual ~IRenderProvider() = default;
};