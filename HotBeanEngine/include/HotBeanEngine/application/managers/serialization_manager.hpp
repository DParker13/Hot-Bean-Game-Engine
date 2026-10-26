#pragma once

#include <HotBeanEngine/core/all_core.hpp>

namespace HBE::Application::Managers {

    class SerializationManager {
    private:
        std::map<std::string, std::shared_ptr<Core::ISerializer>> m_serializers;

    public:
        SerializationManager();
        ~SerializationManager() = default;

        void RegisterSerializer(std::string_view name, std::shared_ptr<Core::ISerializer> serializer);
        void UnRegisterSerializer(std::string_view name);
        std::shared_ptr<Core::ISerializer> GetSerializer(std::string_view name) const;
    };
} // namespace HBE::Application::Managers