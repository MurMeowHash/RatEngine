#pragma once

template<typename... Args>
class IDelegate {
public:
    virtual void Invoke(Args... args) = 0;
    virtual ~IDelegate() = default;
};