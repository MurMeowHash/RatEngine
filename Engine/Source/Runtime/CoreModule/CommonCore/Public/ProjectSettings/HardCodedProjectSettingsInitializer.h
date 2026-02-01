#pragma once

#include "IProjectSettingsInitializer.h"
#include "ProjectSettings.h"

class HardCodedProjectSettingsInitializer : IProjectSettingsInitializer {
public:
    explicit HardCodedProjectSettingsInitializer(ProjectSettings* projectSettings);
    void Initialize() override;
private:
    ProjectSettings* m_projectSettings;
};