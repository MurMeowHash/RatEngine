#pragma once

#include "IClientThread.h"
#include "IConcurrencyFactory.h"
#include "SynchronizationCommon.h"

class ClientThreadBase : IClientThread {
public:
    void Execute() override;
    uint32_t GetThreadId() override;
    bool IsValid() override;
    bool IsRunning() override;

    void Terminate(bool forced) override;

    ~ClientThreadBase() override;
public:
    explicit ClientThreadBase(IConcurrencyFactory* concurrencyFactory);
    void Create(size_t stackSize, ThreadCreationFlags threadCreationFlags) override;
    void SubmitRuntimeFlags(ThreadRuntimeFlags flags) override;
    [[nodiscard]] ThreadRuntimeFlags RetrieveRuntimeFlags();

protected:
    virtual void SubmitWork() = 0;
    virtual void OnRelease() { };

private:
    AtomicSynchronizer<ThreadRuntimeFlags> m_threadRuntimeFlags = AtomicSynchronizer<ThreadRuntimeFlags>(ThreadRuntimeFlags::None);
    IConcurrencyFactory* m_concurrencyFactory;
    IPlatformThread* m_platformThread = nullptr;

    IDelegate<>* m_workDelegate;
};