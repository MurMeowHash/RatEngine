#pragma once

#include "Actor/Actor.h"
#include "../Component/WorldComponent.h"

class WorldScene;

class WorldActor : public Actor<WorldComponent> {
protected:
    void OnComponentSpawned(WorldComponent *component) override;

public:
    explicit WorldActor(DiContainer* diContainer);

    void SetName(const std::string& name);
    [[nodiscard]] std::string GetName() const;
    void AssignRootComponent(WorldComponent* rootComponent);
    [[nodiscard]] WorldComponent* GetRootComponent() const;
private:
    WorldComponent* m_rootComponent = nullptr;
    std::string m_name;
    uint64_t m_id = 0;

friend class WorldScene;
};