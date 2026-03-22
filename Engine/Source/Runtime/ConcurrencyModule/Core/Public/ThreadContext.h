#pragma once

#include <unordered_map>
#include <typeindex>
#include "SynchronizationCommon.h"
#include "IThreadContextUnit.h"

class ThreadContext {
public:
    template<class TThreadContext> requires(std::is_base_of_v<IThreadContextUnit, TThreadContext>)
    void AddContextUnit(TThreadContext* contextUnit) {
        if(IsContextAssembled())
            return;

        m_contextUnits[typeid(TThreadContext)] = contextUnit;
    }

    template<class TThreadContext>
    bool TryRetrieveContextUnit(TThreadContext*& outContext)  {
        if(!IsContextAssembled())
            return false;

        auto contextUnitIterator =  m_contextUnits.find(typeid(TThreadContext));
        if(contextUnitIterator == m_contextUnits.end())
            return false;

        outContext = static_cast<TThreadContext*>(contextUnitIterator->second);
        return true;
    }

    void SetContextAssembled(bool value) {
        m_isContextAssembled.StoreValue(value);
    }

    bool IsContextAssembled() {
        return m_isContextAssembled.RetrieveValue();
    }

    void MarkContextBeingDestroyed() {
        m_isContextBeingDestroyed.StoreValue(true);
    }

    void DestroyContext() {
        if(IsContextBeingDestroyed())
            return;

        MarkContextBeingDestroyed();

        for(const auto& contextUnit : m_contextUnits) {
            delete contextUnit.second;
        }

        m_contextUnits.clear();
    }

    bool IsContextBeingDestroyed() {
        return m_isContextBeingDestroyed.RetrieveValue();
    }

private:
    std::unordered_map<std::type_index, IThreadContextUnit*> m_contextUnits;
    AtomicSynchronizer<bool> m_isContextAssembled = AtomicSynchronizer<bool>(false);
    AtomicSynchronizer<bool> m_isContextBeingDestroyed = AtomicSynchronizer<bool>(false);
};