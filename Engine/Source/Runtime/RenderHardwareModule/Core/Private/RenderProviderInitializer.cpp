#include "RenderProviderInitializer.h"

RenderProviderInitializer::RenderProviderInitializer(IRenderProviderFactory *renderProviderFactory,
                                                     RenderProviderAccessor *renderProviderAccessor,
                                                     IRenderPriorityQueue* renderPriorityQueue)
: m_renderProviderFactory(renderProviderFactory), m_renderProviderAccessor(renderProviderAccessor),m_renderPriorityQueue(renderPriorityQueue) { }

bool RenderProviderInitializer::InitializeRenderProvider(RenderingApi renderingApi) {
    m_renderProviderAccessor->m_renderProvider = m_renderProviderFactory->CreateRenderProvider(renderingApi);
    return m_renderProviderAccessor->m_renderProvider != nullptr;
}

bool RenderProviderInitializer::InitializeRenderProvider() {
    std::vector<RenderingApi> renderPriorityQueue = m_renderPriorityQueue->GetRenderingApiQueue();
    if(renderPriorityQueue.empty())
        return false;

    return InitializeRenderProvider(renderPriorityQueue[0]);
}
