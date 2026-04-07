#pragma once

#include "IConcurrencySystem.h"
#include <type_traits>
#include <map>
#include <typeindex>
#include <set>

class ThreadProcessor {
public:
    explicit ThreadProcessor(uint32_t processedThreadId)
    : m_processedThreadId(processedThreadId) { }

    template<typename TSystem, typename...Args> requires(std::is_base_of_v<IConcurrencySystem, TSystem>)
    void AddSystem(Args... args) {
        auto systemIterator = m_systems.find(typeid(TSystem));
        if (systemIterator != m_systems.end())
            return;

        IConcurrencySystem* system = new TSystem(std::forward<Args>(args)...);
        system->Start(m_processedThreadId);

        m_systems.emplace(typeid(TSystem), system);
    }

    template<typename TSystem> requires(std::is_base_of_v<IConcurrencySystem, TSystem>)
    void RemoveSystem() {
        auto systemIterator = m_systems.find(typeid(TSystem));
        if (systemIterator == m_systems.end())
            return;

        systemIterator->second->Terminate();
        delete systemIterator->second;
        m_systems.erase(systemIterator);
    }

    void Tick() const;
    void TerminateProcessor();

private:
    std::map<std::type_index, IConcurrencySystem*> m_systems;
    uint32_t m_processedThreadId;
};