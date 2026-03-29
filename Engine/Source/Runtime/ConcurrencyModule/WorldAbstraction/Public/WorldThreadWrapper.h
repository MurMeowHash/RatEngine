#pragma once

#include "IClientThreadWrapper.h"

class IPlatformInteractor;
class ThreadContext;
class ProjectSettings;
class ThreadStorage;
class IAllocator;

class WorldThreadWrapper : public IClientThreadWrapper {
public:
    void SubmitRuntimeFlags(ThreadRuntimeFlags flags) override;
    [[nodiscard]] ThreadContext* GetThreadContext() const override;
public:
    [[nodiscard]] uint32_t GetThreadId() override;
    [[nodiscard]] bool IsValid() override;
    [[nodiscard]] bool IsRunning() override;
    void Terminate([[maybe_unused]] bool forced) override;

public:
    WorldThreadWrapper(IPlatformInteractor* platformInteractor, ProjectSettings* projectSettings, ThreadStorage* threadStorage);

    void Initialize() override;
    void Initialize(uint32_t existingThreadId) override;

private:
    IPlatformInteractor* m_platformInteractor;
    ProjectSettings* m_projectSettings;
    ThreadStorage* m_threadStorage;

    uint32_t m_threadId = 0;
    bool m_isRunning = false;
    IAllocator* m_commandBufferAllocator = nullptr;

    ThreadContext* m_threadContext = nullptr;

    void InitializeContext();
};