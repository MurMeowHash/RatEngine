#pragma once

#include "CommandProcessSystem.h"
#include "RenderCommand.h"

class RenderCommandProcessSystem : public CommandProcessSystem<RenderCommand> {
public:
    RenderCommandProcessSystem(ThreadSearchService* threadSearchService, ImmediateCommandExecuteRequest* immediateCommandExecuteRequest)
    : CommandProcessSystem(threadSearchService, immediateCommandExecuteRequest) {}

    void ExecuteCommand(const RenderCommand &processedCommand) override {
        processedCommand();
    }
};