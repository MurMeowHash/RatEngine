#pragma once

class IProjectSettingsInitializer {
public:
    virtual void Initialize() = 0;
    virtual ~IProjectSettingsInitializer() = default;
};