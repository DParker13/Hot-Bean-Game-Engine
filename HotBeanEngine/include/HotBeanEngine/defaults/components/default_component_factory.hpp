#pragma once

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/defaults/components/default_components.hpp>

using namespace HBE::Application;

namespace HBE::Default::Components {

    class DefaultComponentFactory : public IComponentFactory {
        public:
            void RegisterComponents() override;
            void CreateComponentFromYAML(const std::string& component_name, YAML::Node node,
                                        Entity parent_entity, Entity entity) override;
    };
}