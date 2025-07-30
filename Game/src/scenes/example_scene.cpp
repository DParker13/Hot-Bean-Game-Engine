#include "example_scene.hpp"

namespace Scenes {
    void ExampleScene::SetupScene() {
        App& app = App::GetInstance();

        Entity text_entity = TextArchetype::Create();
        app.GetComponent<Text>(text_entity).m_size = 5;
        app.GetComponent<Text>(text_entity).SetText(std::to_string(text_entity));
        app.GetComponent<Text>(text_entity).m_wrapping_width = 50;

        // TODO: When this is created, OnEntityAdded is called for each system and the defaults are used instead
        // Check if there are issues with this approach with transforms.
        Entity shape_entity = ShapeArchetype::Create();
    }

    void ExampleScene::SetupSystems() {
        BaseScene::SetupSystems();

        RegisterSystem<CustomAudioSystem>();
    }
}