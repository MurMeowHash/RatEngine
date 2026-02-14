#pragma once

class IBuildSettingsInitializer {
public:
    virtual void Initialize() = 0;
    virtual ~IBuildSettingsInitializer() = default;
};