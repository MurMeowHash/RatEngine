#pragma once
#include "IRenderer.h"

class DiContainer;
class ILogger;
class RHLRuntimeData;

class ForwardRenderer : public IRenderer {
public:
    ForwardRenderer(ILogger* logger, RHLRuntimeData* rhlRuntimeData);
    void Render() override;
private:
    ILogger* m_logger;
    RHLRuntimeData* m_rhlRuntimeData;
};
