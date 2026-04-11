#pragma once

#include "IRunnableClientThread.h"
#include "IConcurrencyFactory.h"
#include "ThreadContext.h"
#include "ThreadStorage.h"
#include "ThreadProcessor.h"

class EngineCoreEventBus;

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
    ClientThreadBase(IConcurrencyFactory* concurrencyFactory, ThreadStorage* threadStorage, EngineCoreEventBus* engineCoreEventBus);
    void Create(size_t stackSize, ThreadCreationFlags threadCreationFlags) override;
    [[nodiscard]] ThreadContext* GetThreadContext() const override;

public:
    void SubmitRuntimeFlags(ThreadRuntimeFlags flags) override;
    [[nodiscard]] ThreadRuntimeFlags RetrieveRuntimeFlags();

protected:
    ThreadContext* m_threadContext = nullptr;
    IConcurrencyFactory* m_concurrencyFactory;
    ThreadStorage* m_threadStorage;
    EngineCoreEventBus* m_engineCoreEventBus;

    ThreadProcessor* m_threadProcessor = nullptr;

    virtual void SubmitThreadWork() = 0;
    virtual void InitializeContext();
    virtual void OnThreadBegin();
    virtual void OnThreadEnd();

private:
    AtomicSynchronizer<ThreadRuntimeFlags> m_threadRuntimeFlags = AtomicSynchronizer<ThreadRuntimeFlags>(ThreadRuntimeFlags::None);
    IPlatformThread* m_platformThread = nullptr;

    IDelegate<>* m_workDelegate;
    IDelegate<IClientThread*>* m_invokeMemoryBarrierCallback;

    void SubmitWork();
    void InvokeMemoryBarrier(IClientThread* clientThread);
};