/**
 * @file default_component_factory.hpp
 * @author Daniel Parker (DParker13)
 * @brief Used to register and create default components from YAML files
 * @version 0.1
 * @date 2025-07-06
 * 
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/defaults/components/default_components.hpp>

using namespace HBE::Application;

namespace HBE::Default::Components {

    /**
     * @brief Factory for registering and creating default engine components
     */
    class DefaultComponentFactory : public IComponentFactory {
        public:
            void RegisterComponents() override;
            void CreateComponentFromYAML(const std::string& component_name, YAML::Node node,
                                        Entity parent_entity, Entity entity) override;
    };
}