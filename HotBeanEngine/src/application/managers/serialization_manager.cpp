#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/application/managers/serialization_manager.hpp>

// BINARY
#if GAME_RELEASE_BUILD
    #include <HotBeanEngine/serializers/binary/binary_entity_serializer.hpp> // Entity
    #include <HotBeanEngine/serializers/binary/binary_serializer.hpp>        // Basic
#else
    // YAML
    #include <HotBeanEngine/serializers/yaml/yaml_entity_serializer.hpp> // Entity
    #include <HotBeanEngine/serializers/yaml/yaml_serializer.hpp>        // Basic
#endif

namespace HBE::Application::Managers {
    using namespace Serializers;

    /**
     * Register default serializers
     */
    SerializationManager::SerializationManager() {
#if GAME_RELEASE_BUILD
        // BINARY
        RegisterSerializer("BasicSerializer", std::make_shared<BinarySerializer>());
        RegisterSerializer("EntitySerializer", std::make_shared<BinaryEntitySerializer>())
#else
        // YAML
        RegisterSerializer("BasicSerializer", std::make_shared<YamlSerializer>());
        RegisterSerializer("EntitySerializer", std::make_shared<YamlEntitySerializer>());
#endif
    }

    void SerializationManager::RegisterSerializer(std::string_view name,
                                                  std::shared_ptr<Core::ISerializer> serializer) {
        m_serializers.emplace(std::string(name), std::move(serializer));
    }

    void SerializationManager::UnRegisterSerializer(std::string_view name) {
        if (GetSerializer(name)) {
            m_serializers.erase(std::string(name));
        }
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