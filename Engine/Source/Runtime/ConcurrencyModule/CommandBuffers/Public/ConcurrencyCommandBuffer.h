#pragma once

#include "IAllocator.h"
#include "SimpleAllocator.h"
#include <stdexcept>
#include "CoreUtils.h"

template<typename TCommandDelegate>
struct ConcurrencyCommand {
    ConcurrencyCommand(const TCommandDelegate& command, ConcurrencyCommand<TCommandDelegate>* next)
    : m_command(command), m_next(next) { }

    ConcurrencyCommand(const ConcurrencyCommand<TCommandDelegate>& src)
    : m_command(src.m_command), m_next(src.m_next) { }

    TCommandDelegate m_command;
    ConcurrencyCommand<TCommandDelegate>* m_next;
};

template<typename TCommandDelegate>
class ConcurrencyCommandBuffer {
public:
    explicit ConcurrencyCommandBuffer(IAllocator* allocator = nullptr)
    : m_allocator(allocator) {
        if(m_allocator == nullptr) {
            m_allocator = new SimpleAllocator(0);
            m_usedBuiltInAllocator = true;
        }
    }

    ConcurrencyCommand<TCommandDelegate>* GetRoot() const { return m_root; }

    void EqueueCommand(const TCommandDelegate& command) {
        ConcurrencyCommand<TCommandDelegate>* commandNode;
        void* memory = m_allocator->AllocateMemory(sizeof(ConcurrencyCommand<TCommandDelegate>));
        commandNode = new (memory) ConcurrencyCommand<TCommandDelegate>(command, nullptr);
        *m_tail = commandNode;
        m_tail = &commandNode->m_next;
    }

    void TransferCommandBuffer(ConcurrencyCommandBuffer<TCommandDelegate>& srcCommandBuffer, bool invalidateSrcBuffer = true) {
        if(m_root == nullptr) {
            m_root = srcCommandBuffer.m_root;
            m_tail = &m_root;
        }
        else {
            (*m_tail)->m_next = srcCommandBuffer.m_root;
            m_tail = srcCommandBuffer.m_tail;
        }

        TransferMemory(srcCommandBuffer);

        if(invalidateSrcBuffer)
            srcCommandBuffer.Clear();
    }

    void Clear() {
        m_root = nullptr;
        m_tail = &m_root;

        if(m_usedBuiltInAllocator)
            m_allocator->FreeMemory();
    }

    virtual void Submit() = 0;

    ~ConcurrencyCommandBuffer() {
        if(!m_usedBuiltInAllocator)
            return;

        m_allocator->FreeMemory();
        delete m_allocator;
    }

private:
    ConcurrencyCommand<TCommandDelegate>* m_root;
    ConcurrencyCommand<TCommandDelegate>** m_tail = &m_root;

    IAllocator* m_allocator;
    bool m_usedBuiltInAllocator = false;

    void TransferMemory(const ConcurrencyCommandBuffer<TCommandDelegate>& srcCommandBuffer) {
        if(!m_allocator->TryAdopt(srcCommandBuffer.m_allocator))
            throw std::runtime_error(StringFormatter("Failed to transfer memory on command buffer because no transfer defined between",
                                                     typeid(m_allocator).name(),
                                                     " allocator and ",
                                                     typeid(srcCommandBuffer.m_allocator).name()));

        srcCommandBuffer.m_allocator->InvalidateAllocator();
    }
};