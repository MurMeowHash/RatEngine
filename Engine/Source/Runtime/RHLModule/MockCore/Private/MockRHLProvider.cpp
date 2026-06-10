#include "../Public/MockRHLProvider.h"

Rat::RHLProviderModule::ExecResult MockRHLProvider::Initialize() {
    return Rat::RHLProviderModule::ExecResult::IncompatiblePlatform;
}

void MockRHLProvider::Shutdown() { }

uint32_t MockRHLProvider::GetApiVersion() const { return 0; }