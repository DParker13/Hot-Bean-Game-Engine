/**
 * @file shape_system.cpp
 * @author Daniel Parker
 * @brief System for rendering 2D shapes to a texture.
 * @version 0.1
 * @date 2025-09-11
 * 
 * @copyright Copyright (c) 2025
 */

#include <HotBeanEngine/defaults/systems/rendering/shape_system.hpp>

namespace HBE::Default::Systems {
    void ShapeSystem::OnRender() {
        for (auto& entity : m_entities) {
            auto& texture = g_ecs.GetComponent<Texture>(entity);

            if (texture.m_dirty) {
                auto& shape = g_ecs.GetComponent<Shape>(entity);
                auto& transform = g_ecs.GetComponent<Transform2D>(entity);
                auto screen_position = m_camera_system.CalculateScreenPosition(transform.m_world_position);

                SDL_SetRenderTarget(g_app.GetRenderer(), texture.m_texture);
                SDL_SetRenderDrawColor(g_app.GetRenderer(), shape.m_color.r, shape.m_color.g, shape.m_color.b, shape.m_color.a);
                
                switch(shape.m_type) {
                    case Shape::ShapeType::Box: {
                        const SDL_FRect* rect = new SDL_FRect({0, 0, shape.m_size.x, shape.m_size.y});
                        if (shape.m_filled) {
                            SDL_RenderFillRect(g_app.GetRenderer(), rect);
                        }
                        else {
                            SDL_RenderRect(g_app.GetRenderer(), rect);
                        }
                        
                        // Free rect
                        if(rect) {
                            delete rect;
                        }
                    }
                }

                texture.m_dirty = false;
            }
        }
    }

    void ShapeSystem::OnEntityAdded(EntityID entity) {
        CreateTextureForEntity(entity);
    }

    void ShapeSystem::CreateTextureForEntity(EntityID entity) {
        auto& texture = g_ecs.GetComponent<Texture>(entity);
        auto& shape = g_ecs.GetComponent<Shape>(entity);

        if (texture.m_texture == nullptr) {
            texture.m_size = { shape.m_size.x, shape.m_size.y };
            texture.m_texture = SDL_CreateTexture(g_app.GetRenderer(), SDL_PIXELFORMAT_RGBA8888,
                                            SDL_TEXTUREACCESS_TARGET, static_cast<int>(texture.m_size.x), static_cast<int>(texture.m_size.y));
            SDL_SetTextureBlendMode(texture.m_texture, SDL_BLENDMODE_BLEND);
        }
    }
}