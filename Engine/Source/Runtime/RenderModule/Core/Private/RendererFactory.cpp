#include "../Public/RendererFactory.h"
#include "ForwardRenderer.h"
#include <stdexcept>
#include "CoreUtils.h"
#include "DiContainer.h"
#include "ILogger.h"

RendererFactory::RendererFactory(DiContainer *diContainer)
: m_diContainer(diContainer) { }

IRenderer* RendererFactory::CreateRenderer(RendererType rendererType) {
    switch (rendererType) {
        case RendererType::Forward:
            return m_diContainer->Instantiate<ForwardRenderer>().WithArguments<ILogger>();
        default:
            throw std::invalid_argument(StringFormatter("Renderer of type ", static_cast<int>(rendererType), " is not supported"));
    }
}
