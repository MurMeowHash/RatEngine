#pragma once
#include "IDelegate.h"
#include <functional>

template<typename... Args>
class StaticDelegate : public IDelegate<Args...> {
public:
    using FunctionHandler = std::function<void(Args...)>;
    explicit StaticDelegate(const FunctionHandler &functionHandler)
    : m_Func(functionHandler) {}

    void Invoke(Args... args) override {
        m_Func(std::forward<Args>(args)...);
    }

private:
    FunctionHandler m_Func;
};