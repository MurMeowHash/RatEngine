#include "WorldThreadWrapper.h"
#include "PlatformInteractors/IPlatformInteractor.h"
#include "ThreadContext.h"
#include "InfiniteThreadContext.h"
#include "RenderableThreadContext.h"
#include "ProjectSettings/ProjectSettings.h"
#include "LinearAllocator.h"
#include "StaticFunc.h"

WorldThreadWrapper::WorldThreadWrapper(IPlatformInteractor *platformInteractor, ProjectSettings* projectSettings)
: m_platformInteractor(platformInteractor), m_projectSettings(projectSettings) { }

void WorldThreadWrapper::Initialize() {
    m_threadId = m_platformInteractor->GetRunningThreadId();
    InitializeContext();
    m_threadContext->SetContextAssembled(true);
}

uint32_t WorldThreadWrapper::GetThreadId() {
    return m_threadId;
}

void WorldThreadWrapper::Dispose() {
    m_threadContext->DestroyContext();
    delete m_threadContext;
}

void WorldThreadWrapper::InitializeContext() {
    m_threadContext = new ThreadContext;

    m_threadContext->AddContextUnit(new InfiniteThreadContext);
    int maxFramesInFlight = m_projectSettings->GetRenderingSettings().m_maxFramesInFlight;
    m_threadContext->AddContextUnit(new RenderableThreadContext(maxFramesInFlight,
                                                                maxFramesInFlight + 1,
                                                                RENDER_COMMAND_BUFFER_CHUNK_SIZE));
}

ThreadContext *WorldThreadWrapper::GetThreadContext() const {
    return m_threadContext;
}