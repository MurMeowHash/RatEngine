#pragma once

#include <vector>
#include "RenderingApi.h"

class IRenderPriorityQueue {
public:
    [[nodiscard]] virtual std::vector<RenderingApi> GetRenderingApiQueue() const = 0;
    virtual ~IRenderPriorityQueue() = default;
};