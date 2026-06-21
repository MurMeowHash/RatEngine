#include "../Public/WorldScene.h"
#include "Identification/IIdentifierGenerator.h"

void WorldScene::OnActorSpawned(WorldActor *actor) {
    Scene<WorldActor, WorldComponent>::OnActorSpawned(actor);
    actor->m_id = m_actorIdentifierGenerator->GenerateIdentifier();
    AssignUniqueActorName()
}

WorldScene::WorldScene(DiContainer *container)
: Scene(container) { }

void WorldScene::AssignUniqueActorName(WorldActor *actor, const std::string &primaryName) {
    auto actorNameIterator = m_actorNameRegistry.find(primaryName);
    if (actorNameIterator == m_actorNameRegistry.end()) {
        auto actorNameInsertIterator = m_actorNameRegistry.emplace(primaryName, 0);
        actorNameIterator = actorNameInsertIterator.first;
    } else {
        ++actorNameIterator->second;
    }

    if (actorNameIterator->second == 0)
        actor->SetName(actorNameIterator->first);
    else
        actor->SetName(StringFormatter(actorNameIterator->first, ' ', actorNameIterator->second));
}