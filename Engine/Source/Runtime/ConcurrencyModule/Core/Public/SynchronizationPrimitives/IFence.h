#pragma once

class IFence {
public:
    virtual void MakeMemoryVisible() = 0;
    virtual ~IFence() = default;
};