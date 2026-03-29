#pragma once

#include "InfiniteThread.h"

class ProjectSettings;
class IPlatformInteractor;

class RenderThread : public InfiniteThread {
protected:
    void InitializeContext() override;
public:
    RenderThread(IConcurrencyFactory* platformThreadFactory, ThreadStorage* threadStorage,
        ProjectSettings* projectSettings, IPlatformInteractor* platformInteractor);
protected:
    void SubmitInfiniteWork() override;

private:
    ProjectSettings* m_projectSettings;
    IPlatformInteractor* m_platformInteractor;

    void InitializeCommandTreadContext();
};