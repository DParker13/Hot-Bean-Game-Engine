#include "component_manager.hpp"

namespace Core {

    ComponentManager::ComponentManager() : _registeredComponents(0) {}

    ComponentManager::~ComponentManager() = default;

    /**
     * Prints the contents of ComponentManager to the console. This is mostly for
     * debugging purposes and should be removed in a production build.
     */
    std::string ComponentManager::ToString() const {
        std::stringstream str;

        if(_componentNameToType.size() > 0) {
            str << "Component Manager: " << _registeredComponents << "\n";

            for (auto& [componentType, typeName] : _componentTypeToName) {
                str << "  Component Type To Name: (" << componentType << "," << typeName << ")\n";
            }

            for (auto& [typeName, componentType] : _componentNameToType) {
                str << "  Type Name To Component Type: (" << typeName << "," << componentType << ")\n";
            }

            for (auto& [name, sparseSet] : _componentNameToData) {

                str << "  Component Name To Data: " << name << "\n";
                str << sparseSet->ToString();
            }
            str << "\n";
        }

        return str.str();
    }
}