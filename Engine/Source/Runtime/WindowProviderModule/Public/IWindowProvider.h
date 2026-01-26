#pragma once

#include "WindowCreateInfo.h"

class IWindowProvider {
public:
    virtual void CreateWindow(WindowCreateInfo windowCreateInfo) = 0;
};