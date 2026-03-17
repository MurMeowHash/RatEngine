#include "../Public/DiContainer.h"

DiContainer::DiContainer(const DiContainer *parentContainer)
: m_parentContainer(parentContainer) { }

void DiContainer::ResolveDependencies() {
    m_dependencies.clear();

    std::vector<PendingBinding> sortedPendingBindings = TopoSort(m_clientBindings);
    for(const PendingBinding &binding : sortedPendingBindings) {
        m_dependencies[binding.m_bindingType] =
                BindingInstance(binding.m_clientBindingWithInstance->m_clientBinding.m_instantiateFunc(),
                                binding.m_clientBindingWithInstance->m_bindingInstance.m_deleter);
    }
}

void DiContainer::TopoSortUtil(const ClientBindingWithInstance& node,
                               const std::type_index &bindingType,
                               const std::unordered_map<std::type_index, ClientBindingWithInstance>& bindingMap,
                               std::unordered_set<std::type_index>& visited,
                               std::unordered_set<std::type_index>& visiting,
                               std::vector<PendingBinding>& sorted) {
    if (visited.count(bindingType))
        return;

    if (visiting.count(bindingType))
        throw std::runtime_error("Dependency cycle detected");

    visiting.insert(bindingType);

    for (const std::type_index& depType : node.m_clientBinding.m_dependencies) {
        auto bindingIterator = bindingMap.find(depType);
        if (bindingIterator != bindingMap.end())
            TopoSortUtil(bindingIterator->second, bindingIterator->first, bindingMap, visited, visiting, sorted);
        else if(!ContainsDependency(depType))
            throw std::runtime_error(StringFormatter("Dependency not found: ", depType.name()));
    }

    visiting.erase(bindingType);
    visited.insert(bindingType);
    sorted.emplace_back(DiContainer::PendingBinding(&node, bindingType));
}

std::vector<DiContainer::PendingBinding> DiContainer::TopoSort(const std::unordered_map<std::type_index, ClientBindingWithInstance> &bindings) {
    std::unordered_set<std::type_index> visited;
    std::unordered_set<std::type_index> visiting;
    std::vector<DiContainer::PendingBinding> sorted;

    for (const std::pair<const std::type_index, ClientBindingWithInstance>& clientBinding : bindings)
        TopoSortUtil(clientBinding.second, clientBinding.first, bindings, visited, visiting, sorted);

    return sorted;
}

void DiContainer::Destroy() {
    m_clientBindings.clear();

    for(const std::pair<const std::type_index, BindingInstance>& dependency : m_dependencies) {
        dependency.second.m_deleter(dependency.second.m_instance);
    }

    m_dependencies.clear();
}

bool DiContainer::ContainsDependency(const std::type_index &depType) const {
    if(m_dependencies.contains(depType))
        return true;

    if(m_parentContainer)
        return m_parentContainer->ContainsDependency(depType);

    return false;
}
