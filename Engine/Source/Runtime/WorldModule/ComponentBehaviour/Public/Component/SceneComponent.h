#pragma once

#include "Component/Component.h"
#include <vector>
#include "Transform.h"

class SceneComponent : public Component {
public:
    void AttachChild(SceneComponent *child);
    void DetachChild(SceneComponent *child);
    void DetachChildren();
    [[nodiscard]] std::vector<SceneComponent*> GetChildren() const;
    [[nodiscard]] SceneComponent* GetParent() const;
private:
    SceneComponent* m_parent = nullptr;
    std::vector<SceneComponent*> m_children;
    Transform m_transform;
};