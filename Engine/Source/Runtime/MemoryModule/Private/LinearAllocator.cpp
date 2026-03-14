#include "../Public/LinearAllocator.h"
#include <cassert>

LinearAllocator::LinearAllocator(size_t uniformChunkSize)
: AllocatorBase(typeid(LinearAllocator)), m_uniformChunkSize(uniformChunkSize) { }

void *LinearAllocator::AllocateMemory(size_t memorySize) {
    assert(memorySize <= m_uniformChunkSize);

    if(*m_tailChunk == nullptr) {
        *m_tailChunk = new MemoryChunk(m_uniformChunkSize, nullptr);
    }

    if((*m_tailChunk)->m_size + memorySize > (*m_tailChunk)->m_capacity) {
        (*m_tailChunk)->m_next = new MemoryChunk(m_uniformChunkSize, *m_tailChunk);
        m_tailChunk = &(*m_tailChunk)->m_next;
    }

    MemoryChunk* processedChunk = *m_tailChunk;
    if(!processedChunk->IsChunkValid())
        return nullptr;

    void* allocatedMemory = processedChunk->m_memory + processedChunk->m_size;
    processedChunk->m_size += memorySize;
    return allocatedMemory;
}

void LinearAllocator::FreeMemory() {
    MemoryChunk* currentChunk = m_rootChunk;
    while(currentChunk != nullptr) {
        currentChunk->FreeChunk();
        MemoryChunk* inspectedChunk = currentChunk;
        currentChunk = currentChunk->m_next;
        delete inspectedChunk;
    }

    InvalidateAllocator();
}

void LinearAllocator::InvalidateAllocator() {
    m_rootChunk = nullptr;
    m_tailChunk = &m_rootChunk;
}