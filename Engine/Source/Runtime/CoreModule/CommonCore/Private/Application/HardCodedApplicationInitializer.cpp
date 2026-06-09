#include "Application/HardCodedApplicationInitializer.h"

HardCodedApplicationInitializer::HardCodedApplicationInitializer(Application *application)
: m_application(application) {}

void HardCodedApplicationInitializer::Initialize() {
    m_application->SetEngineName("RatEngine");
    m_application->SetEngineVersion(ApplicationVersion{1, 0, 0});
}