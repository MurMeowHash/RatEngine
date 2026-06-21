#pragma once

struct IMapperBase {
    virtual ~IMapperBase() = default;
};

template<typename TMapped, typename TResolved>
struct IRatSubMapper : public IMapperBase {
    virtual TResolved Resolve(TMapped value) = 0;
};