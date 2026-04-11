#pragma once

#include "IConcurrencySystem.h"
#include "ThreadSearchService.h"
#include "ConcurrencyCommandBuffer.h"
#include "Events/ImmediateCommandExecuteRequest.h"
#include "ObjectDelegate.h"

template<typename TCommand>
class CommandProcessSystem : public IConcurrencySystem {
public:
    CommandProcessSystem(ThreadSearchService* threadSearchService, ImmediateCommandExecuteRequest* immediateCommandExecuteRequest)
    : m_threadSearchService(threadSearchService), m_immediateCommandExecuteRequest(immediateCommandExecuteRequest) {
        m_immediateCommandExecuteCallback = new ObjectDelegate<CommandProcessSystem, TCommand>(this, &CommandProcessSystem::ExecuteImmediateCommand);
    }

    ~CommandProcessSystem() override {
        delete m_immediateCommandExecuteCallback;
    }

    void Start(uint32_t localThreadId) override {
        m_localThreadId = localThreadId;
        m_threadSearchService->TryGetThreadContext(m_localThreadId, m_consumerThreadContext);
        m_immediateCommandExecuteRequest->Subscribe<TCommand>(m_immediateCommandExecuteCallback);
    }

    void Tick() override {
        ConcurrencyCommandBuffer<TCommand>* commandBufferToExecute;
        if (m_consumerThreadContext == nullptr || !m_consumerThreadContext->TryGetReadyToExecuteBuffer(commandBufferToExecute))
            return;

        ConcurrencyCommand<TCommand>* processedCommand = commandBufferToExecute->GetRoot();
        while(processedCommand != nullptr) {
            ExecuteCommand(processedCommand->m_command);
            processedCommand = processedCommand->m_next;
        }

        m_consumerThreadContext->MarkBufferExecuted(commandBufferToExecute);
    }

    void Terminate() override {
        m_immediateCommandExecuteRequest->UnSubscribe<TCommand>(m_immediateCommandExecuteCallback);
    }

    virtual void ExecuteCommand(const TCommand& processedCommand) = 0;

private:
    ThreadSearchService* m_threadSearchService;
    ImmediateCommandExecuteRequest* m_immediateCommandExecuteRequest;

    CommandConsumerThreadContext<TCommand>* m_consumerThreadContext = nullptr;
    IDelegate<TCommand>* m_immediateCommandExecuteCallback = nullptr;

    uint32_t m_localThreadId = 0;

    void ExecuteImmediateCommand(TCommand command) {
        ExecuteCommand(command);
    }
};
