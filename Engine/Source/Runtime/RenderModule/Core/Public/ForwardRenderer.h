#pragma once
#include "IRenderer.h"

class DiContainer;
class ILogger;

class ForwardRenderer : public IRenderer {
public:
    explicit ForwardRenderer(ILogger* logger);
    void Render() override;
private:
    ILogger* m_logger;
};
