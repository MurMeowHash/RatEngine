#pragma once

#include "IRunnableClientThread.h"
#include "IConcurrencyFactory.h"
#include "ThreadContext.h"
#include "ThreadStorage.h"

class IPlatformInteractor;

class ClientThreadBase : public IRunnableClientThread {
public:
    void Execute() override;

public:
    uint32_t GetThreadId() override;
    bool IsValid() override;
    bool IsRunning() override;

    void Terminate(bool forced) override;

    ~ClientThreadBase() override;
public:
    ClientThreadBase(IConcurrencyFactory* concurrencyFactory, ThreadStorage* threadStorage, IPlatformInteractor* platformInteractor);
    void Create(size_t stackSize, ThreadCreationFlags threadCreationFlags) override;
    ThreadContext* GetThreadContext() const override;

public:
    void SubmitRuntimeFlags(ThreadRuntimeFlags flags) override;
    [[nodiscard]] ThreadRuntimeFlags RetrieveRuntimeFlags();
    [[nodiscard]] uint32_t GetThreadAuthority() override;
    [[nodiscard]] bool HasThreadAuthority() override;

protected:
    ThreadContext* m_threadContext = nullptr;
    IConcurrencyFactory* m_concurrencyFactory;
    IPlatformInteractor* m_platformInteractor;
    IClientThread* m_authorityThread = nullptr;

    virtual void SubmitWork() = 0;
    virtual void OnRelease() { };
    virtual void InitializeContext();

private:
    AtomicSynchronizer<ThreadRuntimeFlags> m_threadRuntimeFlags = AtomicSynchronizer<ThreadRuntimeFlags>(ThreadRuntimeFlags::None);
    IPlatformThread* m_platformThread = nullptr;
    ThreadStorage* m_threadStorage;

    IDelegate<>* m_workDelegate;
    uint32_t m_threadAuthorityId = 0;

    void AssignThreadAuthority(uint32_t threadAuthorityId);
};