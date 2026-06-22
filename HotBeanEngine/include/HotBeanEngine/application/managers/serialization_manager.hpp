#pragma once

#include <HotBeanEngine/application/managers/logging_manager.hpp>
#include <HotBeanEngine/core/all_core.hpp>

namespace HBE::Application::Managers {

    class SerializationManager {
    private:
        std::shared_ptr<LoggingManager> m_logging_manager;
        std::map<std::string, std::unique_ptr<Core::ISerializer>> m_serializers;

    public:
        SerializationManager(std::shared_ptr<LoggingManager> logging_manager) : m_logging_manager(logging_manager) {}
        ~SerializationManager() = default;

        void RegisterSerializer(std::unique_ptr<Core::ISerializer> serializer);
        std::shared_ptr<Core::ISerializer> GetSerializer(std::string_view name) const;
    };
} // namespace HBE::Application::Managers