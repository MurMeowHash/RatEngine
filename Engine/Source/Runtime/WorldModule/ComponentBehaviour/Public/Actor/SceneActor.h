#pragma once

#include "Actor/Actor.h"
#include "Component/SceneComponent.h"
#include <string>

class SceneActor : public Actor<SceneComponent> {
protected:
    void OnComponentSpawned(SceneComponent *component) override;

public:
    explicit SceneActor(DiContainer* diContainer);

    void SetName(std::string&& name);
    [[nodiscard]] std::string GetName() const;
    void AssignRootComponent(SceneComponent* rootComponent);
    [[nodiscard]] SceneComponent* GetRootComponent() const;
private:
    SceneComponent* m_rootComponent = nullptr;
    std::string m_name;
};