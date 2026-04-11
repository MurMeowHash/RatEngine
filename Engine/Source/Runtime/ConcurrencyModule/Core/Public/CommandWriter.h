#pragma once

#include "ThreadSearchService.h"
#include "PlatformInteractors/IPlatformInteractor.h"
#include "CommandProducerThreadContext.h"
#include "CommandThreadStorage.h"
#include "ConcurrencyGlobals.h"
#include "CoreUtils.h"
#include "Events/ImmediateCommandExecuteRequest.h"

using Rat::ConcurrencyModule::CommandWriteFlags;

class CommandWriter {
public:
    CommandWriter(ThreadSearchService* threadSearchService, IPlatformInteractor* platformInteractor, CommandThreadStorage* commandThreadStorage,
        ImmediateCommandExecuteRequest* immediateCommandExecuteRequest)
    : m_threadSearchService(threadSearchService), m_platformInteractor(platformInteractor), m_commandThreadStorage(commandThreadStorage),
    m_immediateCommandExecuteRequest(immediateCommandExecuteRequest) {}

    template<typename TCommand>
    bool EnqueueCommand(TCommand&& command, CommandWriteFlags writeFlags = CommandWriteFlags::None) {
        uint32_t runningThreadId = m_platformInteractor->GetRunningThreadId();

        if (Rat::Core::Flags::IsFlagSet(writeFlags, CommandWriteFlags::ExecuteImmediate)) {
            uint32_t commandConsumerThreadId = 0;
            if (m_commandThreadStorage->TryRetrieveCommandConsumer<TCommand>(&commandConsumerThreadId) && commandConsumerThreadId == runningThreadId) {
                m_immediateCommandExecuteRequest->Request<TCommand>(std::forward<TCommand>(command));
                return true;
            }
        }

        CommandProducerThreadContext<TCommand>* commandProducerContext;
        if (!m_threadSearchService->TryGetThreadContext(runningThreadId, commandProducerContext))
            return false;

        commandProducerContext->m_commandBuffer->EqueueCommand(std::forward<TCommand>(command));
        return true;
    }

private:
    ThreadSearchService* m_threadSearchService;
    IPlatformInteractor* m_platformInteractor;
    CommandThreadStorage* m_commandThreadStorage;
    ImmediateCommandExecuteRequest* m_immediateCommandExecuteRequest;
};