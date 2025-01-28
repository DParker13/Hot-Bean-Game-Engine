#include "system_manager.hpp"

namespace Core {
    
    SystemManager::SystemManager() {}
    SystemManager::~SystemManager() {
        // Delete all systems from set
        for (auto& entry : _systems) {
            delete entry.second;
        }

        _systems.clear();
    };

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