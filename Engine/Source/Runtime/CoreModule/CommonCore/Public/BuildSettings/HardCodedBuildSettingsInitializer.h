#pragma once

#include "IBuildSettingsInitializer.h"
#include "BuildSettings.h"

class HardCodedBuildSettingsInitializer : public IBuildSettingsInitializer {
public:
    explicit HardCodedBuildSettingsInitializer(BuildSettings* buildSettings);
    void Initialize() override;
private:
    BuildSettings* m_buildSettings;
};