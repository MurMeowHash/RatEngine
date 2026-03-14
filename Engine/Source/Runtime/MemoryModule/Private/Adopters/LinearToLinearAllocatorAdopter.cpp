#include "Adopters/LinearToLinearAllocatorAdopter.h"

//TODO: sussy
void LinearToLinearAllocatorAdopter::Adopt(IAllocator* dest, IAllocator* src) {
    if(dest == src || dest == nullptr || src == nullptr)
        return;

    LinearAllocator* destLinear = static_cast<LinearAllocator*>(dest);
    LinearAllocator* srcLinear = static_cast<LinearAllocator*>(src);

    if(destLinear->m_rootChunk == nullptr) {
        destLinear->m_rootChunk = srcLinear->m_rootChunk;
        destLinear->m_tailChunk = srcLinear->m_tailChunk;
        return;
    }

    MemoryChunk* cutOutChunk = *destLinear->m_tailChunk;
    MemoryChunk* originalAllocatorChunkTail = cutOutChunk->m_parentChunk;

    if((*destLinear->m_tailChunk)->m_parentChunk == nullptr)
        destLinear->m_rootChunk = srcLinear->m_rootChunk;
    else {
        srcLinear->m_rootChunk->m_parentChunk = (*destLinear->m_tailChunk)->m_parentChunk;
        (*destLinear->m_tailChunk)->m_parentChunk->m_next = srcLinear->m_rootChunk;
    }

    if(originalAllocatorChunkTail == nullptr) {
        destLinear->m_rootChunk = cutOutChunk;
        destLinear->m_tailChunk = &destLinear->m_rootChunk;
        return;
    }

    MemoryChunk* inspectedChunk = originalAllocatorChunkTail;
    while(inspectedChunk->m_next != nullptr) {
        inspectedChunk = inspectedChunk->m_next;
    }

    cutOutChunk->m_parentChunk = inspectedChunk;
    inspectedChunk->m_next = cutOutChunk;
    destLinear->m_tailChunk = &inspectedChunk->m_next;
}