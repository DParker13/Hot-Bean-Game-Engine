#pragma once

#include "../gameobject.hpp"

#include "../../components/transform-2d.hpp"
#include "../../components/texture.hpp"

namespace GameObjects {
    namespace UI {
        class UIElement : public GameObject {
        public:
            UIElement(Core::CoreManager* coreManager);
            
            Components::Transform2D& GetTransform2D();
            Components::Texture& GetTexture();
            std::string ToString() const override;
        };
    }
}