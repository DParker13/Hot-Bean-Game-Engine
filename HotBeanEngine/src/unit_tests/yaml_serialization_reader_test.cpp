#include <HotBeanEngine/serializers/yaml/yaml_serialization_reader.hpp>
#include <catch2/catch_all.hpp>

using HBE::Serializers::YamlReader;

TEST_CASE("YamlReader: Section navigation preserves the shared entity tree") {
    const YAML::Node scene = YAML::Load(R"(
Entities:
  - Entity:
      Transform2D:
        layer: 1
      Camera:
        zoom: 1
        viewport_size: [0.5, 1.0]
      Controller:
      Name:
        name: Camera 1
  - Entity:
      Name:
        name: Camera 2
)");
    const std::string original = YAML::Dump(scene);
    const YamlReader reader(scene);
    const YamlReader entities = reader["Entities"];
    REQUIRE(entities.Size() == 2);

    YamlReader components = entities[0]["Entity"];
    std::vector<std::string> component_names;
    for (const auto &component : components) {
        const std::string key = component.first.as<std::string>();
        component_names.push_back(key);
        components.BeginSection(key);
        if (key == "Camera") {
            glm::vec2 viewport_size{0.0f};
            components.Read("viewport_size", viewport_size);
            REQUIRE(viewport_size.x == 0.5f);
            REQUIRE(viewport_size.y == 1.0f);
        }
        else if (key == "Name") {
            std::string name;
            components.Read("name", name);
            REQUIRE(name == "Camera 1");
        }
        components.EndSection();
        REQUIRE(components.Size() == 4);
    }

    REQUIRE(component_names == std::vector<std::string>{"Transform2D", "Camera", "Controller", "Name"});
    REQUIRE(entities.Size() == 2);
    REQUIRE(YAML::Dump(scene) == original);
}

TEST_CASE("YamlReader: Nested sections restore the parent and root") {
    const YAML::Node node = YAML::Load(R"(
Parent:
  value: 10
  Child:
    value: 20
value: 30
)");
    const std::string original = YAML::Dump(node);
    YamlReader reader(node);
    int value = 0;

    reader.BeginSection("Parent");
    reader.BeginSection("Child");
    reader.Read("value", value);
    REQUIRE(value == 20);

    reader.EndSection();
    reader.Read("value", value);
    REQUIRE(value == 10);

    reader.EndSection();
    reader.Read("value", value);
    REQUIRE(value == 30);

    reader.EndSection();
    reader.Read("value", value);
    REQUIRE(value == 30);
    REQUIRE(YAML::Dump(node) == original);
}
