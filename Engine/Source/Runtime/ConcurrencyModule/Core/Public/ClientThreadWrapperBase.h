#pragma once

#include "IClientThreadWrapper.h"

class IPlatformInteractor;
class ThreadContext;
class ProjectSettings;
class ThreadStorage;
class IAllocator;
class IConcurrencyFactory;
class ThreadProcessor;
class DiContainer;
template<typename...Args>
class IDelegate;
class EngineCoreEventBus;

class ClientThreadWrapperBase : public IClientThreadWrapper {
public:
    void SubmitRuntimeFlags(ThreadRuntimeFlags flags) override;
    [[nodiscard]] ThreadContext* GetThreadContext() const override;
public:
    [[nodiscard]] uint32_t GetThreadId() override;
    [[nodiscard]] bool IsValid() override;
    [[nodiscard]] bool IsRunning() override;
    void Terminate([[maybe_unused]] bool forced) override;

public:
    ClientThreadWrapperBase(IPlatformInteractor* platformInteractor, ThreadStorage* threadStorage, IConcurrencyFactory* concurrencyFactory,
        EngineCoreEventBus* engineCoreEventBus);
    ~ClientThreadWrapperBase() override;

    void Initialize() override;
    void Initialize(uint32_t existingThreadId) override;
protected:
    EngineCoreEventBus* m_engineCoreEventBus;

    ThreadContext* m_threadContext = nullptr;
    ThreadProcessor* m_threadProcessor = nullptr;

    virtual void InitializeContext();
    virtual void OnThreadBegin();
    virtual void OnThreadEnd();
private:
    IPlatformInteractor* m_platformInteractor;
    ThreadStorage* m_threadStorage;
    IConcurrencyFactory* m_concurrencyFactory;

    uint32_t m_threadId = 0;
    bool m_isRunning = false;

    IDelegate<IClientThread*>* m_invokeMemoryBarrierCallback;

    void InvokeMemoryBarrier(IClientThread* clientThread);
};