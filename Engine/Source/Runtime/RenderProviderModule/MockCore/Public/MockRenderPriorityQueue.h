#pragma once

#include "IRenderPriorityQueue.h"

class MockRenderPriorityQueue : public IRenderPriorityQueue {
public:
    [[nodiscard]] std::vector<RenderingApi> GetRenderingApiQueue() const override;
};