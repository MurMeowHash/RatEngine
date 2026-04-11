#pragma once

class IRunnable {
public:
    virtual void Execute() = 0;
    virtual ~IRunnable() = default;
};