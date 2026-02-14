#pragma once

#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <typeindex>
#include <functional>
#include <exception>
#include "CoreUtils.h"

struct ClientBinding {
    std::function<void*()> m_instantiateFunc;
    std::vector<std::type_index> m_dependencies;
};

class DiContainer {
public:
    template<typename TTarget>
    void Bind(ClientBinding &&clientBinding) {
        BindingInstance bindingInstance(nullptr, [](void* instance){
            delete static_cast<TTarget*>(instance);
        });

        m_clientBindings[typeid(TTarget)] = ClientBindingWithInstance(std::move(clientBinding), std::move(bindingInstance));
    }

    template<typename TType>
    TType* Resolve() const {
        auto dependencyIterator = m_dependencies.find(typeid(TType));
        if(dependencyIterator == m_dependencies.end())
            throw std::runtime_error(StringFormatter("Unable to resolve dependency ", typeid(TType).name()));

        return static_cast<TType *>(dependencyIterator->second.m_instance);
    }

    void ResolveDependencies();
    void Destroy();
private:
    struct BindingInstance {
        void* m_instance;
        std::function<void(void*)> m_deleter;
    };

    struct ClientBindingWithInstance {
        ClientBinding m_clientBinding;
        BindingInstance m_bindingInstance;
    };

    struct PendingBinding {
        const ClientBindingWithInstance *m_clientBindingWithInstance;
        std::type_index m_bindingType;
    };

    std::unordered_map<std::type_index, ClientBindingWithInstance> m_clientBindings;
    std::unordered_map<std::type_index, BindingInstance> m_dependencies;

    void TopoSortUtil(const ClientBindingWithInstance& node,
                      const std::type_index &bindingType,
                      const std::unordered_map<std::type_index, ClientBindingWithInstance>& bindingMap,
                      std::unordered_set<std::type_index>& visited,
                      std::unordered_set<std::type_index>& visiting,
                      std::vector<PendingBinding>& sorted);

    std::vector<PendingBinding> TopoSort(const std::unordered_map<std::type_index, ClientBindingWithInstance>& bindings);
};