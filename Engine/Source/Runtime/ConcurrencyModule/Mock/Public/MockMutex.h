#pragma once

#include "IMutex.h"

class MockMutex : public IMutex {
public:
    void Create(bool initiallyLocked) override;
    void Lock() override;
    void Unlock() override;
    bool IsValid() override;
    void Terminate() override;
};