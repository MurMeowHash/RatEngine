#include "../Public/ForwardRenderer.h"
#include "ILogger.h"

ForwardRenderer::ForwardRenderer(ILogger *logger)
: m_logger(logger) { }

void ForwardRenderer::Render() {
    m_logger->PrintInfo("Rendering...\n");
}
