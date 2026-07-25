#pragma once

#include <HotBeanEngine/core/all_core.hpp>
#include <HotBeanEngine/factories/icomponent_factory.hpp>

namespace HBE::Application::Managers {

    class SerializationManager {
    private:
        std::map<std::string, std::unique_ptr<Core::ISerializer>> m_serializers;

    public:
        SerializationManager(std::shared_ptr<Factories::IComponentFactory> component_factory);
        ~SerializationManager() = default;

        void RegisterSerializer(std::unique_ptr<Core::ISerializer> serializer);
        std::shared_ptr<Core::ISerializer> GetSerializer(std::string_view name) const;
    };
} // namespace HBE::Application::Managers