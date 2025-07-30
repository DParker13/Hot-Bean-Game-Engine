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

using namespace Core::Components;

namespace Core::Systems {
    void ShapeSystem::SetSignature() {
        SETUP_SYSTEM(ShapeSystem, Transform2D, Texture, Shape);
    }

    void ShapeSystem::OnRender() {
        for (auto entity : m_entities) {
            auto shape = App::GetInstance().GetComponent<Shape>(entity);
        }
    }

    void ShapeSystem::OnEntityAdded(Entity entity) {
        CreateTextureForEntity(entity);
        LayoutVertices(entity);
    }

    void ShapeSystem::CreateTextureForEntity(Entity entity) {
        App& app = App::GetInstance();
        auto texture = app.GetComponent<Texture>(entity);
        auto shape = app.GetComponent<Shape>(entity);

        if (texture.m_texture == nullptr) {
            texture.m_size = { shape.m_size, shape.m_size };
            texture.m_texture = SDL_CreateTexture(app.GetRenderer(), SDL_PIXELFORMAT_RGBA8888,
                                            SDL_TEXTUREACCESS_TARGET, texture.m_size.x, texture.m_size.y);
        }
    }

    void ShapeSystem::LayoutVertices(Entity entity) {
        App& app = App::GetInstance();

        auto shape = app.GetComponent<Shape>(entity);

        if (shape.m_sides < 3) {
            LOG(LoggingType::WARNING, "Shape needs 3 or more sides. Skipping...");
            return;
        }

        auto transform = app.GetComponent<Transform2D>(entity);
        std::array<SDL_Vertex, 3> vertices;
        // for (int i = 0; i < shape.m_sides; i++) {
        //     float offset = glm::cos<float>(shape.m_size / 2);
        //     vertices[i] = { transform.m_world_position.x, transform.m_world_position.x, shape.m_color };
        // }

        float offset = (shape.m_sides * shape.m_size) / 2;
        vertices[0] = { transform.m_world_position.x + offset, transform.m_world_position.y, shape.m_color };
        vertices[1] = { transform.m_world_position.x - offset, transform.m_world_position.y + offset, shape.m_color };
        vertices[2] = { transform.m_world_position.x - offset, transform.m_world_position.y - offset, shape.m_color };
    }
}