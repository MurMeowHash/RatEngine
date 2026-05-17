#pragma once

class ILifecycleMember {
public:
    virtual void Spawned() = 0;
    virtual void Start() = 0;
    virtual void Despawned() = 0;
    virtual ~ILifecycleMember() = default;
};