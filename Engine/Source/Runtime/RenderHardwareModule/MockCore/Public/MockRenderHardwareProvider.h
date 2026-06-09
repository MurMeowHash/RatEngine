#pragma once
#include "IRenderHardwareProvider.h"

class MockRenderHardwareProvider : public IRenderHardwareProvider {
public:
    Rat::RenderHardwareProviderModule::ExecResult Initialize() override;
    void Shutdown() override;
    [[nodiscard]] uint32_t GetApiVersion() const override;
};
