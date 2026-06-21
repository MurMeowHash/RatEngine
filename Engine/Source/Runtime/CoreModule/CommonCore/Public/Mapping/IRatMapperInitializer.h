#pragma once

class IRatMapperInitializer {
public:
    virtual void CreateMapping() = 0;
    virtual void DestroyMapping() = 0;
    virtual ~IRatMapperInitializer() = default;
};