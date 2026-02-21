/**
 * @file example_scene.cpp
 * @author Daniel Parker (DParker13)
 * @brief Implementation of the example game scene.
 * Sets up the initial game scene with cameras, entities, physics, and visual components.
 * @version 0.1
 * @date 2025-06-12
 *
 * @copyright Copyright (c) 2025
 */

#include "example_scene.hpp"
#include <random>

namespace Scenes {
    using namespace HBE::Core;
    using namespace HBE::Default::Components;

    void ExampleScene::SetupScene() {
        int camera_entity = g_ecs.CreateEntity();

        Transform2D camera_transform;
        camera_transform.m_local_position = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
        camera_transform.m_layer = 0;
        Camera camera;
        camera.m_viewport_size = {0.5f, 1.0f};
        Name camera_name;
        camera_name.m_name = "Left Camera";
        g_ecs.AddComponent<Transform2D>(camera_entity, camera_transform);
        g_ecs.AddComponent<Camera>(camera_entity, camera);
        g_ecs.AddComponent<Name>(camera_entity, camera_name);
        g_ecs.AddComponent<Controller>(camera_entity);

        int camera_entity_two = g_ecs.CreateEntity();

        Transform2D camera_transform_two;
        camera_transform_two.m_local_position = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
        camera_transform_two.m_layer = 0;
        Camera camera_two;
        camera_two.m_viewport_size = {0.5f, 1.0f};
        camera_two.m_viewport_position = {0.5f, 0.0f};
        Name camera_name_two;
        camera_name_two.m_name = "Right Camera";
        g_ecs.AddComponent<Name>(camera_entity_two, camera_name_two);
        g_ecs.AddComponent<Transform2D>(camera_entity_two, camera_transform_two);
        g_ecs.AddComponent<Camera>(camera_entity_two, camera_two);
        g_ecs.AddComponent<Controller>(camera_entity_two);

        int floor_entity = g_ecs.CreateEntity();

        Transform2D floor_transform;
        floor_transform.m_local_position = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT};
        floor_transform.m_layer = 0;
        RigidBody floor_rigidbody;
        Collider2D floor_collider;
        floor_collider.m_shape = Collider2D::ColliderShape::Box;
        floor_collider.m_size = {SCREEN_WIDTH, 50.0f};
        Shape floor_shape;
        floor_shape.m_size = floor_collider.m_size;
        floor_shape.m_filled = true;
        Texture floor_texture;
        floor_texture.m_size = floor_collider.m_size;
        Name floor_name;
        floor_name.m_name = "Floor";
        g_ecs.AddComponent<Name>(floor_entity, floor_name);
        g_ecs.AddComponent<Transform2D>(floor_entity, floor_transform);
        g_ecs.AddComponent<RigidBody>(floor_entity, floor_rigidbody);
        g_ecs.AddComponent<Collider2D>(floor_entity, floor_collider);
        g_ecs.AddComponent<Shape>(floor_entity, floor_shape);
        g_ecs.AddComponent<Texture>(floor_entity, floor_texture);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dist_x(0.0f, SCREEN_WIDTH);
        std::uniform_real_distribution<> dist_y(0.0f, SCREEN_HEIGHT / 2.0f);
        std::uniform_real_distribution<> dist_angle(0.0f, 360.0f);
        std::uniform_int_distribution<> dist_size(5, 30);
        std::uniform_int_distribution<> dist_color(0, 255);

        for (int i = 0; i < 400; i++) {
            int box_entity = g_ecs.CreateEntity();

            Transform2D box_transform;
            box_transform.m_local_position = {dist_x(gen), dist_y(gen)};
            box_transform.m_local_rotation = (float)dist_angle(gen);
            box_transform.m_layer = 10;
            RigidBody box_rigidbody;
            box_rigidbody.m_type = b2_dynamicBody;
            Collider2D box_collider;
            box_collider.m_size = {dist_size(gen), dist_size(gen)};
            Shape box_shape;
            box_shape.m_size = box_collider.m_size;
            box_shape.m_color = {(Uint8)dist_color(gen), (Uint8)dist_color(gen), (Uint8)dist_color(gen), 255};
            Texture box_texture;
            box_texture.m_size = box_collider.m_size;
            g_ecs.AddComponent<Transform2D>(box_entity, box_transform);
            g_ecs.AddComponent<RigidBody>(box_entity, box_rigidbody);
            g_ecs.AddComponent<Collider2D>(box_entity, box_collider);
            g_ecs.AddComponent<Shape>(box_entity, box_shape);
            g_ecs.AddComponent<Texture>(box_entity, box_texture);
        }
    }

    void ExampleScene::SetupSystems() { DefaultScene::SetupSystems(); }
} // namespace Scenes