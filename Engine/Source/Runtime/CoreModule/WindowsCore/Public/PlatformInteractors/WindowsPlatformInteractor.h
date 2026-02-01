#pragma once

#include "PlatformInteractors/IPlatformInteractor.h"

class WindowsPlatformInteractor : public IPlatformInteractor {
public:
    void RequestQuit(bool forcedQuit) override;
};