#include "../../Public/Actor/Actor.h"

template<typename TConsumedComponent> requires std::is_base_of_v<IComponent, TConsumedComponent>
Actor<TConsumedComponent>::Actor(DiContainer *diContainer) : m_diContainer(diContainer) { }

template<typename TConsumedComponent> requires std::is_base_of_v<IComponent, TConsumedComponent>
void Actor<TConsumedComponent>::Initialize(IAllocator *componentAllocator) {
    m_componentAllocator = componentAllocator;
}

template<typename TConsumedComponent> requires std::is_base_of_v<IComponent, TConsumedComponent>
void Actor<TConsumedComponent>::DespawnComponent(IComponent *component) {
    auto componentsIterator = m_components.find(typeid(*component));
    if (componentsIterator == m_components.end())
        return;

    std::erase(componentsIterator->second, component);
    component->Despawned();
}