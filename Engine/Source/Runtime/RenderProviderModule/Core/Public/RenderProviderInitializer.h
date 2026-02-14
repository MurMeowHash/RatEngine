#pragma once

#include "IRenderProviderInitializer.h"
#include "IRenderProviderFactory.h"
#include "RenderProviderAccessor.h"
#include "IRenderPriorityQueue.h"

class RenderProviderInitializer : public IRenderProviderInitializer {
public:
    RenderProviderInitializer(IRenderProviderFactory* renderProviderFactory, RenderProviderAccessor* renderProviderAccessor,
                              IRenderPriorityQueue* renderPriorityQueue);
    bool InitializeRenderProvider(RenderingApi renderingApi) override;
    bool InitializeRenderProvider() override;

private:
    IRenderProviderFactory* m_renderProviderFactory;
    RenderProviderAccessor* m_renderProviderAccessor;
    IRenderPriorityQueue* m_renderPriorityQueue;
};