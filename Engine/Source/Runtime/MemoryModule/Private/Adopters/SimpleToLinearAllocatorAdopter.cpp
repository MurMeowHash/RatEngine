#include "Adopters/SimpleToLinearAllocatorAdopter.h"
#include "LinearAllocator.h"
#include "SimpleAllocator.h"

void SimpleToLinearAllocatorAdopter::Adopt(IAllocator *dest, IAllocator *src) {
    if(dest == nullptr || src == nullptr)
        return;

    LinearAllocator* destLinear = static_cast<LinearAllocator*>(dest);
    SimpleAllocator* srcSimple = static_cast<SimpleAllocator*>(src);

    MemoryChunk* currentMemoryChunk = *destLinear->m_tailChunk;
    for(const MemoryCell& simpleAllocatorCell : srcSimple->m_allocatedMemoryCells) {
        if(*destLinear->m_tailChunk == nullptr) {
            *destLinear->m_tailChunk = new MemoryChunk(simpleAllocatorCell.m_memory, simpleAllocatorCell.m_memorySize, nullptr);
            currentMemoryChunk = *destLinear->m_tailChunk;
        } else {
            currentMemoryChunk->m_next = new MemoryChunk(simpleAllocatorCell.m_memory, simpleAllocatorCell.m_memorySize, currentMemoryChunk);
            currentMemoryChunk = currentMemoryChunk->m_next;
        }
    }
}