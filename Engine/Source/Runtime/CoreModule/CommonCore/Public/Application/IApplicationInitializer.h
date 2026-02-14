#pragma once

class IApplicationInitializer {
public:
    virtual void Initialize() = 0;
    virtual ~IApplicationInitializer() = default;
};