#pragma once

class IPlatformInteractor {
public:
    virtual void RequestQuit(bool forcedQuit) = 0;
    virtual ~IPlatformInteractor() = default;
};