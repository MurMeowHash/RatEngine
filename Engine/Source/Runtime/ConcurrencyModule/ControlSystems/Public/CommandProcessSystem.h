#pragma once

#include "IConcurrencySystem.h"
#include "CommandConsumerThreadContext.h"
#include "ThreadSearchService.h"
#include "ConcurrencyCommandBuffer.h"

template<typename TCommand>
class CommandProcessSystem : public IConcurrencySystem {
public:
    explicit CommandProcessSystem(ThreadSearchService* threadSearchService)
    : m_threadSearchService(threadSearchService) {}

    void Start(uint32_t localThreadId) override {
        m_localThreadId = localThreadId;
        m_threadSearchService->TryGetThreadContext(m_localThreadId, m_consumerThreadContext);
    }

    void Tick() override {
        ConcurrencyCommandBuffer<TCommand>* commandBufferToExecute;
        if (m_consumerThreadContext == nullptr || !m_consumerThreadContext->TryGetReadyToExecuteBuffer(commandBufferToExecute))
            return;

        ConcurrencyCommand<TCommand>* processedCommand = commandBufferToExecute->GetRoot();
        while(processedCommand != nullptr) {
            processedCommand->m_command();
            processedCommand = processedCommand->m_next;
        }

        m_consumerThreadContext->MarkBufferExecuted(commandBufferToExecute);
    }

    void Terminate() override {

    }

private:
    ThreadSearchService* m_threadSearchService;
    CommandConsumerThreadContext<TCommand>* m_consumerThreadContext = nullptr;

    uint32_t m_localThreadId = 0;
};
