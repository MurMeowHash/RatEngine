#pragma once

#include "IApplicationInitializer.h"
#include "Application.h"

class HardCodedApplicationInitializer : public IApplicationInitializer {
public:
    explicit HardCodedApplicationInitializer(Application* application);
    void Initialize() override;
private:
    Application* m_application = nullptr;
};