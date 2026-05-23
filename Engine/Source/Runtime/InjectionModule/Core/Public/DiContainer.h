#pragma once

#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <typeindex>
#include <functional>
#include "CoreUtils.h"
#include "IAllocator.h"

class DiContainer;

struct ClientBinding {
    std::function<void*(DiContainer*)> m_instantiateFunc;
    std::vector<std::type_index> m_dependencies;
};

template<typename TInstance, typename TTarget>
struct BindingAssembler {
    BindingAssembler(DiContainer* diContainer)
    : m_diContainer(diContainer) { }

    template<typename TTargetOverride>
    BindingAssembler<TInstance, TTargetOverride> To() {
        BindingAssembler<TInstance, TTargetOverride> overriddenBinding = BindingAssembler<TInstance, TTargetOverride>(m_diContainer);
        m_isOverridden = true;
        return overriddenBinding;
    }

    template<typename...Args>
    void WithArguments();

    ~BindingAssembler();

private:
    DiContainer* m_diContainer;
    ClientBinding m_assembledBinding;

    bool m_isOverridden = false;
};

template<typename TInstance>
struct InstanceAssembler {
    explicit InstanceAssembler(const DiContainer* diContainer)
    : m_diContainer(diContainer) { }

    InstanceAssembler UseAllocator(IAllocator* allocator);

    template<typename...Args>
    TInstance* WithArguments() const;
private:
    const DiContainer* m_diContainer;
    IAllocator* m_allocator = nullptr;
};

//TODO: make thread-safe
class DiContainer {
public:
    explicit DiContainer(const DiContainer* parentContainer = nullptr);

    template<typename TTarget>
    void Bind(ClientBinding &&clientBinding) {
        BindingInstance bindingInstance(nullptr, [](void* instance){
            delete static_cast<TTarget*>(instance);
        });

        m_clientBindings[typeid(TTarget)] = ClientBindingWithInstance(std::move(clientBinding), std::move(bindingInstance));
    }

    template<typename TInstance>
    BindingAssembler<TInstance, TInstance> Bind() {
        return BindingAssembler<TInstance, TInstance>(this);
    }

    template<typename TType>
    TType* Resolve() const {
        auto dependencyIterator = m_dependencies.find(typeid(TType));
        if(dependencyIterator != m_dependencies.end())
            return static_cast<TType *>(dependencyIterator->second.m_instance);

        if(m_parentContainer)
            return m_parentContainer->Resolve<TType>();

        throw std::runtime_error(StringFormatter("Unable to resolve dependency ", typeid(TType).name()));
    }

    template<typename TInstance>
    InstanceAssembler<TInstance> Instantiate() const {
        return InstanceAssembler<TInstance>(this);
    }

    bool ContainsDependency(const std::type_index& depType) const;

    template<typename TType>
    bool ContainsDependency() const {
        return ContainsDependency(typeid(TType));
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
    const DiContainer* m_parentContainer = nullptr;

    void TopoSortUtil(const ClientBindingWithInstance& node,
                      const std::type_index &bindingType,
                      const std::unordered_map<std::type_index, ClientBindingWithInstance>& bindingMap,
                      std::unordered_set<std::type_index>& visited,
                      std::unordered_set<std::type_index>& visiting,
                      std::vector<PendingBinding>& sorted);

    std::vector<PendingBinding> TopoSort(const std::unordered_map<std::type_index, ClientBindingWithInstance>& bindings);
};

template<typename TInstance, typename TTarget>
template<typename ... Args>
void BindingAssembler<TInstance, TTarget>::WithArguments() {
    m_assembledBinding.m_instantiateFunc = [](DiContainer* diContainer) {
        return new TInstance(diContainer->Resolve<Args>()...);
    };

    m_assembledBinding.m_dependencies = std::vector<std::type_index>{ typeid(Args)... };
}

template<typename TInstance, typename TTarget>
BindingAssembler<TInstance, TTarget>::~BindingAssembler() {
    if (m_isOverridden)
        return;

    m_diContainer->Bind<TTarget>(std::move(m_assembledBinding));
}

template<typename TInstance>
InstanceAssembler<TInstance> InstanceAssembler<TInstance>::UseAllocator(IAllocator *allocator) {
    m_allocator = allocator;
    return *this;
}

template<typename TInstance>
template<typename ... Args>
TInstance* InstanceAssembler<TInstance>::WithArguments() const {
    if (m_allocator != nullptr) {
        void* instanceMemory = m_allocator->AllocateMemory(sizeof(TInstance));
        return new (instanceMemory) TInstance(m_diContainer->Resolve<Args>()...);
    }

    return new TInstance(m_diContainer->Resolve<Args>()...);
}
