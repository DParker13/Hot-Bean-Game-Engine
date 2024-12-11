#include "component_manager.hpp"

namespace Core {

    ComponentManager::ComponentManager() : _registeredComponents(0) {}

    ComponentManager::~ComponentManager() = default;

    /**
     * Prints the contents of ComponentManager to the console. This is mostly for
     * debugging purposes and should be removed in a production build.
     */
    void ComponentManager::Print() const {
        if(_componentNameToType.size() > 0) {
            std::cout << "Component Manager: " << _registeredComponents << std::endl;

            for (auto& [componentType, typeName] : _componentTypeToName) {
                std::cout << "  Component Type To Name: " << "(" << componentType << "," << typeName << ")" << std::endl;
            }

            for (auto& [typeName, componentType] : _componentNameToType) {
                std::cout << "  Type Name To Component Type: " << "(" << typeName << "," << componentType << ")" << std::endl;
            }

            for (auto& [name, sparseSet] : _componentNameToData) {

                std::cout << "  Component Name To Data: " << name << std::endl;
                sparseSet->Print();
            }
            std::cout << std::endl;
        }
    }
}