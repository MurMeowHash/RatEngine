#pragma once

#include "ThreadSearchService.h"
#include "PlatformInteractors/IPlatformInteractor.h"
#include "CommandProducerThreadContext.h"

class CommandWriter {
public:
    CommandWriter(ThreadSearchService* threadSearchService, IPlatformInteractor* platformInteractor)
    : m_threadSearchService(threadSearchService), m_platformInteractor(platformInteractor) {}

    template<typename TCommand>
    bool EnqueueCommand(TCommand&& command) {
        CommandProducerThreadContext<TCommand>* commandProducerContext;
        if (!m_threadSearchService->TryGetThreadContext(m_platformInteractor->GetRunningThreadId(), commandProducerContext))
            return false;

        commandProducerContext->m_commandBuffer->EqueueCommand(std::move(command));
        return true;
    }

private:
    ThreadSearchService* m_threadSearchService;
    IPlatformInteractor* m_platformInteractor;
};