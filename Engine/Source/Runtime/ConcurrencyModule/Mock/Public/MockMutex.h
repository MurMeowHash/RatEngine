#pragma once

#include "IMutex.h"

class MockMutex : public IMutex {
public:
    void Create(bool initiallyLocked) override;
    void Lock() const override;
    void Unlock() const override;
    bool IsValid() const override;
    void Terminate() override;
};