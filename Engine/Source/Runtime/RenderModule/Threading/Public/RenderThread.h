#pragma once

#include "ClientThreadBase.h"

class RenderThread : public ClientThreadBase {
public:
    explicit RenderThread(IConcurrencyFactory* platformThreadFactory);
protected:
    void SubmitWork() override;
};