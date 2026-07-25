#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/application/managers/serialization_manager.hpp>
#include <HotBeanEngine/serializers/binary/binary_scene_serializer.hpp>
#include <HotBeanEngine/serializers/yaml/yaml_scene_serializer.hpp>

namespace HBE::Application::Managers {
    SerializationManager::SerializationManager(std::shared_ptr<Factories::IComponentFactory> component_factory) {
        // Register default serializers
        RegisterSerializer(std::make_unique<Serializers::YamlSceneSerializer>(component_factory));
        RegisterSerializer(std::make_unique<Serializers::BinarySceneSerializer>(component_factory));
    }

    void SerializationManager::RegisterSerializer(std::unique_ptr<Core::ISerializer> serializer) {
        m_serializers.emplace(serializer->GetName(), std::move(serializer));
    }

    std::shared_ptr<Core::ISerializer> SerializationManager::GetSerializer(std::string_view name) const {
        auto it = m_serializers.find(std::string(name));
        if (it != m_serializers.end()) {
            return std::shared_ptr<Core::ISerializer>(it->second.get(), [](Core::ISerializer *) {});
        }
        else {
            LOG(LoggingType::ERROR, "Serializer not found: " + std::string(name));
            return nullptr;
        }
    }
} // namespace HBE::Application::Managers