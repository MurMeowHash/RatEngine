#pragma once

#include "IDelegate.h"
#include <functional>

template<typename TObject, typename... Args>
class ObjectDelegate : public IDelegate<Args...> {
public:
    using MemberFunctionHandler = void(TObject::*)(Args...);

    ObjectDelegate(TObject *object, MemberFunctionHandler memberFunctionHandler)
    : m_object(object), m_MemberFunc(memberFunctionHandler) {}

    void Invoke(Args... args) override {
        (m_object->*m_MemberFunc)(std::forward<Args>(args)...);
    }

    void operator()(Args... args) override {
        Invoke(std::forward<Args>(args)...);
    }

private:
    TObject *m_object;
    MemberFunctionHandler m_MemberFunc;
};