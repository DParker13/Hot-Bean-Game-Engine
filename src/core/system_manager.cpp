#include "system_manager.hpp"

namespace Core {
    
    SystemManager::SystemManager() {}
    SystemManager::~SystemManager() = default;

    /**
     * Prints the contents of SystemManager to the console. This is mostly for
     * debugging purposes and should be removed in a production build.
     */
    void SystemManager::Print() const {
        std::cout << "System Manager:" << std::endl;

        for (auto& [name, system] : _systems) {
            std::cout << "  System Signature: " << _signatures.at(name) << std::endl;
            system->Print();
            std::cout << std::endl;
        }
    }
}