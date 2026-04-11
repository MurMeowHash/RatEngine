#pragma once

#include "ThreadRunnerAssembler.h"
#include "ThreadStorage.h"

class ThreadRunner {
public:
    ThreadRunner(DiContainer* diContainer, CommandThreadStorage* commandThreadStorage, ThreadStorage* threadStorage);

    template<typename TThread> requires std::is_base_of_v<IRunnableClientThread, TThread>
    ThreadInstanceAssembler<TThread> StartThread() {
        return ThreadInstanceAssembler<TThread>(m_diContainer, m_commandThreadStorage);
    }

    template<typename TThread> requires std::is_base_of_v<IClientThreadWrapper, TThread>
    ThreadWrapperInstanceAssembler<TThread> StartThreadWrapper() {
        return ThreadWrapperInstanceAssembler<TThread>(m_diContainer, m_commandThreadStorage);
    }

    void StopThreads();

private:
    DiContainer* m_diContainer;
    CommandThreadStorage* m_commandThreadStorage;
    ThreadStorage* m_threadStorage;
};