#pragma once

#include "ClientThreadBase.h"

class RenderThread : public ClientThreadBase {
public:
    explicit RenderThread(IPlatformThreadFactory* platformThreadFactory);
protected:
    void SubmitWork() override;
};