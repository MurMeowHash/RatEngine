#include "../Public/ForwardRenderer.h"
#include "ILogger.h"
#include "RHLRuntimeData.h"

ForwardRenderer::ForwardRenderer(ILogger *logger, RHLRuntimeData* rhlRuntimeData)
: m_logger(logger), m_rhlRuntimeData(rhlRuntimeData) { }

void ForwardRenderer::Render() {
    m_logger->PrintInfo("Rendering...\n");
    IRHLTexture* rhlTexture = m_rhlRuntimeData->m_rhlProvider->CreateTexture(RHLTextureCreateInfo());
}