#pragma once

#include "IRunnableClientThread.h"
#include "IClientThreadWrapper.h"
#include "DiContainer.h"
#include "CommandThreadStorage.h"

template<typename TThread> requires std::is_base_of_v<IClientThread, TThread>
struct ThreadAssembler {
    ThreadAssembler(CommandThreadStorage* commandThreadStorage)
    : m_commandThreadStorage(commandThreadStorage) {}

    template<typename...Args>
    ThreadAssembler& AssignCommandAuthority() {
        (m_commandThreadStorage->AssignCommandAuthority<Args>(m_threadInstance->GetThreadId()), ...);
        return *this;
    }

    template<typename...Args>
    ThreadAssembler& AssignCommandConsumer() {
        (m_commandThreadStorage->SetCommandConsumer<Args>(m_threadInstance->GetThreadId()), ...);
        return *this;
    }

    [[nodiscard]] TThread* RetrieveThread() const {
        return m_threadInstance;
    }

protected:
    TThread* m_threadInstance = nullptr;

private:
    CommandThreadStorage* m_commandThreadStorage;
};

template<typename TThread> requires std::is_base_of_v<IRunnableClientThread, TThread>
struct ThreadInstanceAssembler : public ThreadAssembler<TThread> {
    ThreadInstanceAssembler(DiContainer* diContainer, CommandThreadStorage* commandThreadStorage)
    : ThreadAssembler<TThread>(commandThreadStorage), m_diContainer(diContainer) {}

    template<typename...Args>
    ThreadAssembler<TThread>& Create(size_t stackSize, ThreadCreationFlags threadCreationFlags) {
        this->m_threadInstance = new TThread(m_diContainer->Resolve<Args>()...);
        this->m_threadInstance->Create(stackSize, threadCreationFlags);
        return *this;
    }

private:
    DiContainer* m_diContainer;
};

template<typename TThread> requires std::is_base_of_v<IClientThreadWrapper, TThread>
struct ThreadWrapperInstanceAssembler : public ThreadAssembler<TThread> {
    ThreadWrapperInstanceAssembler(DiContainer* diContainer, CommandThreadStorage* commandThreadStorage)
    : ThreadAssembler<TThread>(commandThreadStorage), m_diContainer(diContainer) {}

    template<typename...Args>
    ThreadAssembler<TThread>& Create(uint32_t existingThreadId) {
        this->m_threadInstance = new TThread(m_diContainer->Resolve<Args>()...);
        this->m_threadInstance->Initialize(existingThreadId);
        return *this;
    }

private:
    DiContainer* m_diContainer;
};