#include "../Public/Runner/ThreadRunner.h"

ThreadRunner::ThreadRunner(DiContainer *diContainer, CommandThreadStorage *commandThreadStorage, ThreadStorage *threadStorage)
: m_diContainer(diContainer), m_commandThreadStorage(commandThreadStorage), m_threadStorage(threadStorage) { }

void ThreadRunner::StopThreads() {
    std::vector<IClientThread*> allThreads = m_threadStorage->GetAllThreads();
    for (IClientThread* thread : allThreads) {
        thread->SubmitRuntimeFlags(ThreadRuntimeFlags::StopRequested);
    }

    for (IClientThread* thread : allThreads) {
        thread->Terminate(false);
        delete thread;
    }
}
