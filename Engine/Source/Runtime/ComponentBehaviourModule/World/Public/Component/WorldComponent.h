#pragma once

#include "Component/Component.h"
#include <vector>
#include "Transform.h"

class WorldComponent : public Component {
public:
    void AttachChild(WorldComponent *child);
    void DetachChild(WorldComponent *child);
    void DetachChildren();
    [[nodiscard]] std::vector<WorldComponent*> GetChildren() const;
    [[nodiscard]] WorldComponent* GetParent() const;
private:
    WorldComponent* m_parent = nullptr;
    std::vector<WorldComponent*> m_children;
    Transform m_transform;
};