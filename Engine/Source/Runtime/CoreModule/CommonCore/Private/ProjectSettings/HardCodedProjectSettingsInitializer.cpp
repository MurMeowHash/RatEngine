#include "../../Public/ProjectSettings/HardCodedProjectSettingsInitializer.h"

HardCodedProjectSettingsInitializer::HardCodedProjectSettingsInitializer(ProjectSettings* projectSettings)
: m_projectSettings(projectSettings) { }

void HardCodedProjectSettingsInitializer::Initialize() {
    GeneralSettings generalSettings = GeneralSettings("RatEngine");
    WindowSettings windowSettings = WindowSettings(800, 600, false);
    m_projectSettings->SetGeneralSettings(generalSettings);
    m_projectSettings->SetWindowSettings(windowSettings);
}
