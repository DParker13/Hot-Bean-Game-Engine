/**
 * @file render_system.cpp
 * @author Daniel Parker
 * @brief Rendering system implementation.
 * Responsible for rendering game entities to the screen using SDL.
 * @version 0.1
 * @date 2025-02-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "shape_system.hpp"

using namespace HBE::Components;

namespace Systems {
    void ShapeSystem::OnRender() {
        for (auto entity : m_entities) {
            auto shape = g_ecs.GetComponent<Shape>(entity);
            auto transform = g_ecs.GetComponent<Transform2D>(entity);

            SDL_SetRenderTarget(g_app.GetRenderer(), g_ecs.GetComponent<Texture>(entity).m_texture);
            SDL_SetRenderDrawColor(g_app.GetRenderer(), shape.m_color.r, shape.m_color.g, shape.m_color.b, shape.m_color.a);
            
            switch(shape.m_type) {
                case Shape::ShapeType::Box: {
                    SDL_Rect rect = {transform.m_world_position.x, transform.m_world_position.y, shape.m_size.x, shape.m_size.y};
                    SDL_RenderDrawRect(g_app.GetRenderer(), &rect);
                }
            }

            SDL_SetRenderTarget(g_app.GetRenderer(), nullptr);
        }
    }

    void ShapeSystem::OnEntityAdded(Entity entity) {
        CreateTextureForEntity(entity);
    }

    void ShapeSystem::CreateTextureForEntity(Entity entity) {
        auto texture = g_ecs.GetComponent<Texture>(entity);
        auto shape = g_ecs.GetComponent<Shape>(entity);

        if (texture.m_texture == nullptr) {
            texture.m_size = { shape.m_size.x, shape.m_size.y };
            texture.m_texture = SDL_CreateTexture(g_app.GetRenderer(), SDL_PIXELFORMAT_RGBA8888,
                                            SDL_TEXTUREACCESS_TARGET, texture.m_size.x, texture.m_size.y);
        }
    }
}