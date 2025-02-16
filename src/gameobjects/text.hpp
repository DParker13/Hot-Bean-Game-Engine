#pragma once

#include "gameobject.hpp"

#include "../components/transform.hpp"
#include "../components/text.hpp"
#include "../components/texture.hpp"

namespace GameObjects {
    class Text : public GameObject {
    public:
        Text(Core::CoreManager* coreManager);
        
        Components::Transform& GetTransform();
        Components::Text& GetText();
        Components::Texture& GetTexture();
        std::string ToString() const override;
    };
}