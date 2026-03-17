#pragma once

#include "IRenderPriorityQueue.h"

class WindowsRenderPriorityQueue : public IRenderPriorityQueue {
public:
    [[nodiscard]] std::vector<RenderingApi> GetRenderingApiQueue() const override;
};