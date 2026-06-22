#include <HotBeanEngine/application/managers/serialization_manager.hpp>

namespace HBE::Application::Managers {
    void SerializationManager::RegisterSerializer(std::unique_ptr<Core::ISerializer> serializer) {
        m_serializers.emplace(serializer->GetName(), std::move(serializer));
    }

    std::shared_ptr<Core::ISerializer> SerializationManager::GetSerializer(std::string_view name) const {
        auto it = m_serializers.find(std::string(name));
        if (it != m_serializers.end()) {
            return std::shared_ptr<Core::ISerializer>(it->second.get(), [](Core::ISerializer *) {});
        }
        else {
            LOG_CORE(LoggingType::ERROR, "Serializer not found: " + std::string(name));
            return nullptr;
        }
    }
} // namespace HBE::Application::Managers