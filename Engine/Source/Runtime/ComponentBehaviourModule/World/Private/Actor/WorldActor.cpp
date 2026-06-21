#include "../../Public/Actor/WorldActor.h"

void WorldActor::OnComponentSpawned(WorldComponent *component) {
    Actor<WorldComponent>::OnComponentSpawned(component);
    if (m_rootComponent == nullptr)
        m_rootComponent = component;
    else
        m_rootComponent->AttachChild(component);
}

WorldActor::WorldActor(DiContainer *diContainer)
: Actor(diContainer) { }

void WorldActor::SetName(const std::string& name) {
    m_name = name;
}

std::string WorldActor::GetName() const {
    return m_name;
}

void WorldActor::AssignRootComponent(WorldComponent *rootComponent) {
    m_rootComponent = rootComponent;
}

WorldComponent * WorldActor::GetRootComponent() const {
    return m_rootComponent;
}