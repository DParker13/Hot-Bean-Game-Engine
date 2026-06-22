/**
 * @file component_factory.hpp
 * @author Daniel Parker (DParker13)
 * @brief Used to register and create default components from serialized data
 * @version 0.1
 * @date 2025-07-06
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <HotBeanEngine/factories/icomponent_factory.hpp>

namespace HBE::Factories {
    /**
     * @brief Factory for registering and creating default engine components
     */
    class ComponentFactory : public IComponentFactory {
    public:
        void RegisterComponents() override;
        void CreateComponent(const std::string &component_name, Core::ISerializationReader &reader,
                             Core::EntityID parent_entity, Core::EntityID entity) override;
    };
} // namespace HBE::Factories