#pragma once

#include <cstdint>

class IConcurrencySystem {
public:
    virtual void Start(uint32_t localThreadId) = 0;
    virtual void Tick() = 0;
    virtual void Terminate() = 0;
    virtual ~IConcurrencySystem() = default;
};