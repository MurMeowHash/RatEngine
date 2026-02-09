#pragma once

#include "IRenderProvider.h"

class MockRenderProvider : public IRenderProvider {
public:
    Rat::RenderProviderModule::ExecResult Initialize() override { return Rat::RenderProviderModule::ExecResult::APINotSupported; }
    [[nodiscard]] uint32_t GetApiVersion() const override { return 0; }
    [[nodiscard]] bool CanContinueExecution(const Rat::RenderProviderModule::ExecResult &execResult) const override { return false; }
};
