#pragma once

#include "IRatMapperInitializer.h"
#include "RatMapper.h"
#include "IAllocator.h"

class RatMapperInitializerBase : public IRatMapperInitializer {
public:
    RatMapperInitializerBase(RatMapper* ratMapper, uint32_t preAllocatedMemory);
    ~RatMapperInitializerBase() override;

    void DestroyMapping() override;
protected:
    template<typename TMapped, typename TResolved, typename TSubMapper>
    void AddMapping() {
        void* memory = m_mappingAllocator->AllocateMemory(sizeof(TSubMapper));
        m_ratMapper->AddMapping<TMapped, TResolved>(new (memory) TSubMapper());
    }

private:
    RatMapper* m_ratMapper;
    IAllocator* m_mappingAllocator;
};
