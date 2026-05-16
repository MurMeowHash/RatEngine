#pragma once

#include <set>

class SceneActor;
class IAllocator;

class Scene {
public:
    SceneActor* SpawnActor();
    void DespawnActor(SceneActor* actor);
private:
    IAllocator* m_allocator;
    std::set<SceneActor*> m_actors;
};