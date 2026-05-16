#include "../../Public/Component/SceneComponent.h"

void SceneComponent::AttachChild(SceneComponent *child) {
    m_children.push_back(child);
    child->m_parent = this;
}

void SceneComponent::DetachChild(SceneComponent *child) {
    std::erase(m_children, child);
    child->m_parent = nullptr;
}

void SceneComponent::DetachChildren() {
    for (SceneComponent* child : m_children) {
        child->m_parent = nullptr;
    }

    m_children.clear();
}

std::vector<SceneComponent *> SceneComponent::GetChildren() const {
    return m_children;
}

SceneComponent * SceneComponent::GetParent() const {
    return m_parent;
}