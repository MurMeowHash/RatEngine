#pragma once

#include <type_traits>
#include "Component/IComponent.h"
#include "DiContainer.h"
#include "IAllocator.h"
#include "ILifecycleMember.h"
#include <unordered_map>

template<typename TConsumedComponent> requires std::is_base_of_v<IComponent, TConsumedComponent>
class Actor : public ILifecycleMember {
public:
    void Spawned() override {}
    void Start() override {}
    void Despawned() override {}

public:
    explicit Actor(DiContainer* diContainer);

    void Initialize(IAllocator* componentAllocator);

    template<typename TComponent, typename...Args> requires std::is_base_of_v<TConsumedComponent, TComponent>
    TComponent* SpawnComponent() {
        TComponent* component = m_diContainer->Instantiate<TComponent>()
            .UseAllocator(m_componentAllocator)
            .template WithArguments<Args...>();

        m_components[typeid(TComponent)].emplace_back(component);
        component->Spawned();
        OnComponentSpawned(component);
        return component;
    }

    void DespawnComponent(IComponent* component);

    template<typename TComponent> requires std::is_base_of_v<TConsumedComponent, TComponent>
    bool TryGetComponent(TComponent*& component) {
        auto componentsIterator = m_components.find(typeid(TComponent));
        if (componentsIterator == m_components.end() || componentsIterator->second.empty())
            return false;

        component = componentsIterator->second.front();
        return true;
    }

    template<typename TComponent> requires std::is_base_of_v<TConsumedComponent, TComponent>
    bool TryGetAllComponents(std::vector<TComponent*>& components) {
        auto componentsIterator = m_components.find(typeid(TComponent));
        if (componentsIterator == m_components.end())
            return false;

        components = componentsIterator->second;
        return true;
    }

protected:
    virtual void OnComponentSpawned([[maybe_unused]] TConsumedComponent* component) {}

private:
    std::unordered_map<std::type_index, std::vector<IComponent*>> m_components;
    IAllocator* m_componentAllocator = nullptr;
    DiContainer* m_diContainer;
};