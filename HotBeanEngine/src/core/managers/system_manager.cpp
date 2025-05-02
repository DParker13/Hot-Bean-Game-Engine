/**
 * @file system_manager.cpp
 * @author Daniel Parker (DParker13)
 * @brief Manages component-system relationship.
 * 
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "system_manager.hpp"

namespace Core::Managers {
    /**
     * Prints the contents of SystemManager to the console. This is mostly for
     * debugging purposes and should be removed in a production build.
     */
    std::string SystemManager::ToString() const {
        std::stringstream str;
        str << "System Manager:\n";

        for (auto& [name, system] : _systems) {
            str << "  System Signature: " << _signatures.at(name) << "\n";
            str << system->ToString() << "\n";
        }

        return str.str();
    }
}