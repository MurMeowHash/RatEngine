#pragma once

class IMutex {
public:
    virtual void Create() = 0;
    [[nodiscard]] virtual bool IsValid() const = 0;
    virtual void LockExclusive() const = 0;
    virtual void UnlockExclusive() const = 0;
    virtual void LockShared() = 0;
    virtual void UnlockShared() = 0;
    virtual void Terminate() = 0;
    virtual ~IMutex() = default;
};