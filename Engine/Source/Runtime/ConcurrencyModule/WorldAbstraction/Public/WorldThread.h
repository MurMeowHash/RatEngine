#pragma once

#include "ClientThreadWrapperBase.h"

class ProjectSettings;
class IAllocator;
class DiContainer;
namespace EngineCoreEvents {
    class EngineBeginFrameEvent;
}

class WorldThread : public ClientThreadWrapperBase {
protected:
    void InitializeContext() override;
    void OnThreadBegin() override;
    void OnThreadEnd() override;

public:
    WorldThread(IPlatformInteractor* platformInteractor, ThreadStorage* threadStorage, IConcurrencyFactory* concurrencyFactory,
                       EngineCoreEventBus* engineCoreEventBus, ProjectSettings* projectSettings, DiContainer* diContainer);
    ~WorldThread() override;

private:
    ProjectSettings* m_projectSettings;
    DiContainer* m_diContainer;

    IDelegate<const EngineCoreEvents::EngineBeginFrameEvent&>* m_engineBeginFrameCallback;

    uint32_t m_threadId = 0;
    bool m_isRunning = false;
    IAllocator* m_commandBufferAllocator = nullptr;

    void OnEngineBeginFrame(const EngineCoreEvents::EngineBeginFrameEvent& beginFrameEventData);
};