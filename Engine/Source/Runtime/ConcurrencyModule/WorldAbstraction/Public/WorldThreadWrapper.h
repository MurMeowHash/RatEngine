#pragma once

#include "IClientThreadWrapper.h"

class IPlatformInteractor;
class ThreadContext;
class InfiniteThreadContext;
class RenderableThreadContext;
class ProjectSettings;
template<typename TReturn, typename... Args>
class IFunc;
class IAllocator;

class WorldThreadWrapper : public IClientThreadWrapper {
public:
    [[nodiscard]] uint32_t GetThreadId() override;
    [[nodiscard]] bool IsValid() override;
    [[nodiscard]] bool IsRunning() override;
    void Terminate(bool forced) override;

public:
    WorldThreadWrapper(IPlatformInteractor* platformInteractor, ProjectSettings* projectSettings);

    void Initialize() override;
    void Initialize(uint32_t existingThreadId) override;
    void Dispose() override;
    [[nodiscard]] ThreadContext* GetThreadContext() const override;

private:
    static constexpr size_t RENDER_COMMAND_BUFFER_CHUNK_SIZE = 4096;

    IPlatformInteractor* m_platformInteractor;
    ProjectSettings* m_projectSettings;

    uint32_t m_threadId = 0;

    ThreadContext* m_threadContext = nullptr;
    InfiniteThreadContext* m_cachedInfiniteThreadContext = nullptr;
    RenderableThreadContext* m_cachedRenderableThreadContext = nullptr;
    IFunc<IAllocator*>* m_renderCommandBufferAllocFunc = nullptr;

    void InitializeContext();
};