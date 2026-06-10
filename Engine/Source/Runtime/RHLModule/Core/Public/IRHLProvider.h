#pragma once

class IRHLProvider {
public:
    [[nodiscard]] virtual bool Initialize() = 0;
    virtual void Shutdown() = 0;
    virtual ~IRHLProvider() = default;
};