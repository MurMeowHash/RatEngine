#pragma once

class IMutex {
public:
    virtual void Create(bool initiallyLocked) = 0;
    virtual void Lock() const = 0;
    virtual void Unlock() const = 0;
    [[nodiscard]] virtual bool IsValid() const = 0;
    virtual void Terminate() = 0;
    virtual ~IMutex() = default;
};