#include "../../Public/Installers/RenderModuleCoreInstaller.h"
#include "RendererFactory.h"

void RenderModuleCoreInstaller::InstallBindings(DiContainer *diContainer) const {
    diContainer->Bind<RendererFactory>().To<IRendererFactory>().WithArguments<DiContainer>();
}
