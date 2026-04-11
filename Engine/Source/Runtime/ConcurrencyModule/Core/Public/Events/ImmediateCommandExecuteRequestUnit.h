#pragma once

#include "Event.h"

template<typename TCommand>
struct ImmediateCommandExecuteRequestUnit {
    static ImmediateCommandExecuteRequestUnit<TCommand>* GetInstance() {
        if (m_instance == nullptr) {
            m_instance = new ImmediateCommandExecuteRequestUnit<TCommand>();
        }

        return m_instance;
    }

    static void Dispose() {
        delete m_instance;
        m_instance = nullptr;
    }

    Event<TCommand> m_immediateCommandExecuteRequested;

    void Request(TCommand&& command) {
        m_immediateCommandExecuteRequested.Invoke(std::forward<TCommand>(command));
    }

private:
    static ImmediateCommandExecuteRequestUnit<TCommand>* m_instance;
};

template<typename TCommand>
ImmediateCommandExecuteRequestUnit<TCommand>* ImmediateCommandExecuteRequestUnit<TCommand>::m_instance = nullptr;