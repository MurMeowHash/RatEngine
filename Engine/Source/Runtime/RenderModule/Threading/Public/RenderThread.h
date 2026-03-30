#pragma once

#include "InfiniteThread.h"

class ProjectSettings;
class IPlatformInteractor;

class RenderThread : public InfiniteThread {
protected:
    void InitializeContext() override;
public:
    RenderThread(IConcurrencyFactory* platformThreadFactory, ThreadStorage* threadStorage,
        IPlatformInteractor* platformInteractor, ProjectSettings* projectSettings);
protected:
    void SubmitInfiniteWork() override;

private:
    ProjectSettings* m_projectSettings;

    void InitializeCommandTreadContext();
};