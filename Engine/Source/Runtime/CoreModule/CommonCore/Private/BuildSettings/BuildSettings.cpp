#include "BuildSettings/BuildSettings.h"

void BuildSettings::SetIsDevelopmentBuild(bool isDevelopment) {
    m_isDevelopmentBuild = isDevelopment;
}

bool BuildSettings::GetIsDevelopmentBuild() const {
    return m_isDevelopmentBuild;
}
