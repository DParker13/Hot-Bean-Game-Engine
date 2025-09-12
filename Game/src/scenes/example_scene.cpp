#include "example_scene.hpp"

namespace Scenes {
    void ExampleScene::SetupScene() {
        Octree2D<int> octree = Octree2D<int>(glm::ivec3(0, 0, Config::SCREEN_HEIGHT), 10);
        std::vector<glm::ivec3> all_bounds = octree.GetAllBounds();
        for (int i = 0; i < all_bounds.size(); i++) {
            Entity e = g_ecs.CreateEntity();

            Transform2D transform = Transform2D();
            transform.m_world_position = glm::vec2(all_bounds[i].x, all_bounds[i].y);

            Shape shape = Shape();
            shape.m_type = Shape::ShapeType::Box;
            shape.m_size = glm::vec2(all_bounds[i].z, all_bounds[i].z);
            shape.m_color = { 255, 0, 0, 255 };

            g_ecs.AddComponent<Shape>(e, shape);
            g_ecs.AddComponent<Transform2D>(e, transform);
            g_ecs.AddComponent<Texture>(e);
        }
    }

    void ExampleScene::SetupSystems() {
        BaseScene::SetupSystems();

        RegisterSystem<CustomAudioSystem>();
    }
}