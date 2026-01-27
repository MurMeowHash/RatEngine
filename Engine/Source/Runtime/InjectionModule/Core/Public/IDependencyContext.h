#pragma once

class IDependencyContext {
public:
    virtual void OpenContext() = 0;
    virtual void CloseContext() = 0;
    virtual const DiContainer& GetContainer() const = 0;
    virtual ~IDependencyContext() = default;
};