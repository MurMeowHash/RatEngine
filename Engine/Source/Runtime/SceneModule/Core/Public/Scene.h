#pragma once

#include <set>
#include "DiContainer.h"
#include "Actor/Actor.h"

class IAllocator;

template<typename TActor, typename TActorComponent> requires std::is_base_of_v<Actor<TActorComponent>, TActor>
class Scene {
public:
    explicit Scene(DiContainer* container) : m_diContainer(container) {}

    virtual ~Scene() = default;

    template<typename...Args>
    TActor* SpawnActor() {
        TActor* actor = m_diContainer->Instantiate<TActor>()
        .UseAllocator(m_actorAllocator)
        .template WithArguments<Args...>();

        m_actors.emplace(actor);
        OnActorSpawned(actor);
        return actor;
    }

    void DespawnActor(TActor *actor) {
        auto actorIterator = m_actors.find(actor);
        if (actorIterator == m_actors.end())
            return;

        m_actors.erase(actorIterator);
    }

    void PlaceActor(TActor* actor) {
        auto actorIterator = m_actors.find(actor);
        if (actorIterator != m_actors.end())
            return;

        m_actors.emplace(actor);
    }

    void RemoveActor(TActor* actor) {
        m_actors.erase(actor);
    }

protected:
    std::set<TActor*> m_actors;

    virtual void OnActorSpawned([[maybe_unused]] TActor* actor) {}

private:
    DiContainer* m_diContainer;
    IAllocator* m_actorAllocator = nullptr;
};
