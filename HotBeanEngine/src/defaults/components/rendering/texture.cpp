/**
 * @file texture.cpp
 * @author Daniel Parker (DParker13)
 * @brief Texture component. Used for rendering textures.
 * @version 0.1
 * @date 2026-03-15
 *
 * @copyright Copyright (c) 2026
 */

#include <HotBeanEngine/defaults/components/rendering/texture.hpp>

#include <HotBeanEngine/editor/property_nodes/texture_preview.hpp>
#include <HotBeanEngine/editor/property_nodes/vec2.hpp>

namespace HBE::Default::Components {
    using namespace Application::GUI::PropertyNodes;

    Texture::~Texture() {
        if (m_texture) {
            SDL_DestroyTexture(m_texture);
        }
    }

    void Texture::Serialize(YAML::Emitter &out) const { out << YAML::Key << "size" << YAML::Value << m_size; }

    void Texture::RenderProperties(int &id) {
        if (Vec2::RenderProperty(id, "Size", m_size, {0.0f, 0.0f})) {
            MarkDirty();
        }

        TexturePreview::RenderProperty(id, "Texture Preview", m_texture);
    }
} // namespace HBE::Default::Components