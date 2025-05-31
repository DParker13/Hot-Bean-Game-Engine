#include "test_scene.hpp"

namespace Scenes {
    void TestScene::SetupScene() {
        App& app = App::GetInstance();

        Entity text_entity = app.CreateEntity();
        app.AddComponent<Text>(text_entity, Text());
        app.AddComponent<Transform2D>(text_entity, Transform2D());
        app.AddComponent<Texture>(text_entity, Texture());
        app.GetComponent<Text>(text_entity)._size = 5;
        app.GetComponent<Text>(text_entity).SetText(std::to_string(text_entity));
        app.GetComponent<Text>(text_entity)._wrapping_width = 50;
        app.GetComponent<Text>(text_entity)._dirty = true;

    }

    void TestScene::UnloadScene() {}
}