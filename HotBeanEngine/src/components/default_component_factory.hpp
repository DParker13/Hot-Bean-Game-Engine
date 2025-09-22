#pragma once

#include "component_factory.hpp"
#include "default_components.hpp"

namespace HBE::Application {

    class DefaultComponentFactory : public IComponentFactory {
        public:
            void RegisterComponents() override;
            void CreateComponentFromYAML(const std::string& component_name, YAML::Node node,
                                        Entity parent_entity, Entity entity) override;
    };
}