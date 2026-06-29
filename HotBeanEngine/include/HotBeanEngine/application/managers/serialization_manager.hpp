#pragma once

#include <HotBeanEngine/core/all_core.hpp>

namespace HBE::Application::Managers {

    class SerializationManager {
    private:
        std::map<std::string, std::unique_ptr<Core::ISerializer>> m_serializers;

    public:
        SerializationManager() = default;
        ~SerializationManager() = default;

        void RegisterSerializer(std::unique_ptr<Core::ISerializer> serializer);
        std::shared_ptr<Core::ISerializer> GetSerializer(std::string_view name) const;
    };
} // namespace HBE::Application::Managers