#include "BuildSettings/HardCodedBuildSettingsInitializer.h"

HardCodedBuildSettingsInitializer::HardCodedBuildSettingsInitializer(BuildSettings *buildSettings)
: m_buildSettings(buildSettings) { }

void HardCodedBuildSettingsInitializer::Initialize() {
    m_buildSettings->SetIsDevelopmentBuild(true);
}