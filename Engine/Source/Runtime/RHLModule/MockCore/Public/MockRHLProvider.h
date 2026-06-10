#pragma once
#include "IRHLProvider.h"

class MockRHLProvider : public IRHLProvider {
public:
    [[nodiscard]] bool Initialize() override;
    void Shutdown() override;
    [[nodiscard]] uint32_t GetApiVersion() const override;
};
