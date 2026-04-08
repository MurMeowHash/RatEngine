#pragma once

#include "CommandProcessSystem.h"
#include "RenderCommand.h"

class RenderCommandProcessSystem : public CommandProcessSystem<RenderCommand> {
public:
    RenderCommandProcessSystem(ThreadSearchService* threadSearchService, ILogger* logger, IPlatformInteractor* platformInteractor)
    : CommandProcessSystem(threadSearchService), m_logger(logger), m_platformInteractor(platformInteractor) {}

    void ExecuteCommand(ConcurrencyCommand<RenderCommand> *processedCommand) override {
        processedCommand->m_command(m_logger, m_platformInteractor);
    }

private:
    ILogger* m_logger;
    IPlatformInteractor* m_platformInteractor;
};