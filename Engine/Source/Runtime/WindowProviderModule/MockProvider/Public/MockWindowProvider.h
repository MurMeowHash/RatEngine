#pragma once

#include "IWindowProvider.h"

class MockWindowProvider : IWindowProvider {
public:
    Rat::WindowProviderModule::ExecResult CreateMainWindow(const WindowCreateInfo &windowCreateInfo) override {
        return Rat::WindowProviderModule::ExecResult::PlatformNotSupported;
    }

    void Tick() override {}

    void Shutdown() override {}
};