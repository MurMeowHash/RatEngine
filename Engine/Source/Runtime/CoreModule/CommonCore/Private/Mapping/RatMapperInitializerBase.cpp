#include "../../Public/Mapping/RatMapperInitializerBase.h"
#include "LinearAllocator.h"

RatMapperInitializerBase::RatMapperInitializerBase(RatMapper *ratMapper, uint32_t preAllocatedMemory)
: m_ratMapper(ratMapper) {
    m_mappingAllocator = new LinearAllocator(preAllocatedMemory);
}

RatMapperInitializerBase::~RatMapperInitializerBase() {
    delete m_mappingAllocator;
}

void RatMapperInitializerBase::DestroyMapping() {
    m_ratMapper->ClearMapping();
    m_mappingAllocator->FreeMemory();
}