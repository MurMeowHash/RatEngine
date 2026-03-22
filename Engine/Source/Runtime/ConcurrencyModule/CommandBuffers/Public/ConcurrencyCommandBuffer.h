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

template<typename TCommand>
class ConcurrencyCommandBuffer {
public:
    explicit ConcurrencyCommandBuffer(IAllocator* allocator = nullptr)
    : m_allocator(allocator) {
        if(m_allocator == nullptr) {
            m_allocator = new SimpleAllocator(0);
            m_usedBuiltInAllocator = true;
        }
    }

    ConcurrencyCommand<TCommand>* GetRoot() const { return m_root; }

    void EqueueCommand(const TCommand& command) {
        void* memory = m_allocator->AllocateMemory(sizeof(ConcurrencyCommand<TCommand>));
        ConcurrencyCommand<TCommand> *commandNode = new(memory) ConcurrencyCommand<TCommand>(command, nullptr);
        *m_tail = commandNode;
        m_tail = &commandNode->m_next;
    }

    void TransferCommandBuffer(ConcurrencyCommandBuffer<TCommand>& srcCommandBuffer, bool invalidateSrcBuffer = true) {
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

    virtual ~ConcurrencyCommandBuffer() {
        if(!m_usedBuiltInAllocator)
            return;

        m_allocator->FreeMemory();
        delete m_allocator;
    }

private:
    ConcurrencyCommand<TCommand>* m_root;
    ConcurrencyCommand<TCommand>** m_tail = &m_root;

    IAllocator* m_allocator;
    bool m_usedBuiltInAllocator = false;

    void TransferMemory(const ConcurrencyCommandBuffer<TCommand>& srcCommandBuffer) {
        if(!m_allocator->TryAdopt(srcCommandBuffer.m_allocator))
            throw std::runtime_error(StringFormatter("Failed to transfer memory on command buffer because no transfer defined between",
                                                     typeid(m_allocator).name(),
                                                     " allocator and ",
                                                     typeid(srcCommandBuffer.m_allocator).name()));

        srcCommandBuffer.m_allocator->InvalidateAllocator();
    }
};