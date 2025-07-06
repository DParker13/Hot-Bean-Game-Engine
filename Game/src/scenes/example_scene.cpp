#include "example_scene.hpp"

namespace Scenes {
    void ExampleScene::SetupScene() {
        App& app = App::GetInstance();

        Entity text_entity = TextArchetype::Create();
        app.GetComponent<Text>(text_entity).m_size = 5;
        app.GetComponent<Text>(text_entity).SetText(std::to_string(text_entity));
        app.GetComponent<Text>(text_entity).m_wrapping_width = 50;
    }

    void ExampleScene::SetupPreSystems() {
        BaseScene::SetupPreSystems();

        RegisterSystem<CustomAudioSystem>();
    }
}