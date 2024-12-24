#pragma once

#include "gameobject.hpp"

#include "../components/transform.hpp"
#include "../components/text.hpp"

namespace GameObjects {
    class Text : public GameObject {
    public:
        Text(Core::CoreManager* coreManager);
        
        Components::Transform& GetTransform();
        Components::Text& GetText();
        std::string ToString() const override;
    };
}