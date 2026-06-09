#include "../Public/MockRenderHardwareProvider.h"

Rat::RenderHardwareProviderModule::ExecResult MockRenderHardwareProvider::Initialize() {
    return Rat::RenderHardwareProviderModule::ExecResult::IncompatiblePlatform;
}

void MockRenderHardwareProvider::Shutdown() { }

uint32_t MockRenderHardwareProvider::GetApiVersion() const { return 0; }