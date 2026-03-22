#pragma once

template<typename TReturn, typename... Args>
class IFunc {
public:
    virtual TReturn Invoke(Args... args) = 0;
    virtual TReturn operator()(Args... args) = 0;
    virtual ~IFunc() = default;
};