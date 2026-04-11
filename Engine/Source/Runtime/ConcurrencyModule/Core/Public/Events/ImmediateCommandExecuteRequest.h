#pragma once

#include "ImmediateCommandExecuteRequestUnit.h"

struct ImmediateCommandExecuteRequest {
    template<typename TCommand>
    void Subscribe(IDelegate<TCommand>* callback) {
        ImmediateCommandExecuteRequestUnit<TCommand>::GetInstance()->m_immediateCommandExecuteRequested += callback;
    }

    template<typename TCommand>
    void UnSubscribe(IDelegate<TCommand>* callback) {
        ImmediateCommandExecuteRequestUnit<TCommand>::GetInstance()->m_immediateCommandExecuteRequested -= callback;
        ImmediateCommandExecuteRequestUnit<TCommand>::Dispose();
    }

    template<typename TCommand>
    void Request(TCommand&& command) {
        ImmediateCommandExecuteRequestUnit<TCommand>::GetInstance()->Request(std::forward<TCommand>(command));
    }
};