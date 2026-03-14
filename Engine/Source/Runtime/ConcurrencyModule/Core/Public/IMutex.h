#pragma once

class IMutex {
public:
    virtual void Create(bool initiallyLocked) = 0;
    virtual void Lock() = 0;
    virtual void Unlock() = 0;
    [[nodiscard]] virtual bool IsValid() = 0;
    virtual void Terminate() = 0;
    virtual ~IMutex() = default;
};