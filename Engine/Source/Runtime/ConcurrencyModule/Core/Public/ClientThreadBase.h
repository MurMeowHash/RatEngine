#pragma once

#include "IClientThread.h"
#include "IPlatformThreadFactory.h"

class ClientThreadBase : IClientThread {
public:
    void Execute() override;
    uint32_t GetThreadId() override;
    bool IsValid() override;
    bool IsRunning() override;

    void Terminate(bool forced) override;

    ~ClientThreadBase() override;
public:
    explicit ClientThreadBase(IPlatformThreadFactory* platformThreadFactory);
    void Create(size_t stackSize, ThreadCreationFlags threadCreationFlags) override;
    void SubmitRuntimeFlags(ThreadRuntimeFlags flags) override;
    [[nodiscard]] ThreadRuntimeFlags RetrieveRuntimeFlags();

protected:
    virtual void SubmitWork() = 0;
    virtual void OnRelease() { };

private:
    ThreadRuntimeFlags m_threadRuntimeFlags = ThreadRuntimeFlags::None;
    IPlatformThreadFactory* m_platformThreadFactory;
    IPlatformThread* m_platformThread = nullptr;

    IDelegate<>* m_workDelegate;
};