#include "tile.hpp"

namespace GameObjects {
    
    /**
     * Creates a new player object
     *
     * @param coreManager The CoreManager object managing the ECS
     */
    Tile::Tile(Core::CoreManager* coreManager)
        : GameObject(coreManager) {
        _coreManager->AddComponent<Components::Transform2D>(_entity, Components::Transform2D());
        _coreManager->AddComponent<Components::Tile>(_entity, Components::Tile());
    }

    Components::Transform2D& Tile::GetTransform2D() {
        return _coreManager->GetComponent<Components::Transform2D>(_entity);
    }

    Components::Tile& Tile::GetTile() {
        return _coreManager->GetComponent<Components::Tile>(_entity);
    }
    
    std::string Tile::ToString() const {
        return _coreManager->ToString();
    };
}