#pragma once

#include "CommandProcessSystem.h"
#include "RenderCommand.h"

class RenderCommandProcessSystem : public CommandProcessSystem<RenderCommand> {
public:
    RenderCommandProcessSystem(ThreadSearchService* threadSearchService, ImmediateCommandExecuteRequest* immediateCommandExecuteRequest,
                               ILogger* logger, IPlatformInteractor* platformInteractor)
    : CommandProcessSystem(threadSearchService, immediateCommandExecuteRequest), m_logger(logger), m_platformInteractor(platformInteractor) {}

    void ExecuteCommand(const RenderCommand &processedCommand) override {
        processedCommand(m_logger, m_platformInteractor);
    }

private:
    ILogger* m_logger;
    IPlatformInteractor* m_platformInteractor;
};