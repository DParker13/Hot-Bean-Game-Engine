#pragma once

#include "gameobject.hpp"

#include "../components/transform.hpp"
#include "../components/text.hpp"

namespace GameObjects {
    class Text : public IGameObject {
    public:
        Entity entity;
        Core::CoreManager* coreManager;

        Text(Core::CoreManager* coreManager);
        Components::Transform& GetTransform();
        Components::Text& GetText();
        std::string ToString(Core::CoreManager& coreManager) const override;
    };
}