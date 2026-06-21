#pragma once

#include <set>
#include "Scene.h"

template<typename TSimulationActor, typename TSimulationActorComponent>
class Simulation {
public:
    void RegisterScene(Scene<TSimulationActor, TSimulationActorComponent>* scene) {
        if (m_scenes.count(scene))
            return;

        m_scenes.insert(scene);
    }

    void UnregisterScene(Scene<TSimulationActor, TSimulationActorComponent>* scene) {
        m_scenes.erase(scene);
    }

private:
    std::set<Scene<TSimulationActor, TSimulationActorComponent>*> m_scenes;
};