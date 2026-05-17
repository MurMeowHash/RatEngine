#pragma once

#include "Scene.h"
#include "Actor/WorldActor.h"

template<typename T>
class IIdentifierGenerator;

class WorldScene : public Scene<WorldActor, WorldComponent> {
protected:
    void OnActorSpawned(WorldActor *actor) override;

public:
    explicit WorldScene(DiContainer* container);

private:
    IIdentifierGenerator<uint64_t>* m_actorIdentifierGenerator = nullptr;

    std::unordered_map<std::string, int> m_actorNameRegistry;

    void AssignUniqueActorName(WorldActor* actor, const std::string &primaryName);
};