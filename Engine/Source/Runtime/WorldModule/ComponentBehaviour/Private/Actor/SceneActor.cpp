#include "../../Public/Actor/SceneActor.h"

void SceneActor::OnComponentSpawned(SceneComponent *component) {
    Actor<SceneComponent>::OnComponentSpawned(component);
    if (m_rootComponent == nullptr)
        m_rootComponent = component;
    else
        m_rootComponent->AttachChild(component);
}

SceneActor::SceneActor(DiContainer *diContainer)
: Actor(diContainer) { }

void SceneActor::SetName(std::string &&name) {
    m_name = std::move(name);
}

std::string SceneActor::GetName() const {
    return m_name;
}

void SceneActor::AssignRootComponent(SceneComponent *rootComponent) {
    m_rootComponent = rootComponent;
}

SceneComponent * SceneActor::GetRootComponent() const {
    return m_rootComponent;
}
