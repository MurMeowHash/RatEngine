#include "../../Public/Component/WorldComponent.h"

void WorldComponent::AttachChild(WorldComponent *child) {
    m_children.push_back(child);
    child->m_parent = this;
}

void WorldComponent::DetachChild(WorldComponent *child) {
    std::erase(m_children, child);
    child->m_parent = nullptr;
}

void WorldComponent::DetachChildren() {
    for (WorldComponent* child : m_children) {
        child->m_parent = nullptr;
    }

    m_children.clear();
}

std::vector<WorldComponent *> WorldComponent::GetChildren() const {
    return m_children;
}

WorldComponent * WorldComponent::GetParent() const {
    return m_parent;
}