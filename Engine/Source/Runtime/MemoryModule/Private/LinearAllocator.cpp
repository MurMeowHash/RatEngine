#include "../Public/LinearAllocator.h"
#include <cassert>

LinearAllocator::LinearAllocator(size_t uniformChunkSize)
: AllocatorBase(typeid(LinearAllocator)), m_uniformChunkSize(uniformChunkSize) { }

void *LinearAllocator::AllocateMemory(size_t memorySize) {
    assert(memorySize <= m_uniformChunkSize);

    if(*m_tailChunk == nullptr) {
        *m_tailChunk = new MemoryChunk(m_uniformChunkSize, nullptr);
    }

    MemoryChunk* processedChunk = *m_tailChunk;
    size_t alignment = alignof(std::max_align_t);
    size_t alignedOffset = AlignForward(processedChunk->m_size, alignment);

    if(alignedOffset + memorySize > processedChunk->m_capacity) {
        processedChunk->m_next = new MemoryChunk(m_uniformChunkSize, *m_tailChunk);
        m_tailChunk = &(*m_tailChunk)->m_next;
        processedChunk = *m_tailChunk;

        alignedOffset = AlignForward(0, alignment);
    }

    if(!processedChunk->IsChunkValid())
        return nullptr;

    void* allocatedMemory = processedChunk->m_memory + alignedOffset;
    processedChunk->m_size = alignedOffset + memorySize;
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

size_t LinearAllocator::AlignForward(size_t ptr, size_t alignment) {
    return (ptr + (alignment - 1)) & ~(alignment - 1);
}