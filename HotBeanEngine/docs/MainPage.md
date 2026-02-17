# Hot Bean Engine

## Overview

**Hot Bean Engine** is a custom 2D video game engine created using **SDL3**. It provides a robust foundation for developing 2D games with a modern Entity-Component-System (ECS) architecture inspired by Austin Morlan's ECS design.

## Key Features

### Core Architecture
- **ECS Framework**: Entity-Component-System architecture for flexible entity management and data-driven design
- **Sparse Sets**: Efficient component storage using sparse set data structures for optimal memory layout and cache performance
- **System Lifecycle**: Comprehensive system lifecycle hooks (OnStart, OnPreEvent, OnEvent, OnFixedUpdate, OnUpdate, OnRender, OnPostRender)
- **Signature-Based Filtering**: Automatic entity matching based on component signatures

### Default Systems and Components
- **Physics**: Box2D integration for 2D physics simulation with collision detection
- **Rendering**: Multi-layer rendering system with camera support
- **Input**: Keyboard and mouse input handling via SDL3
- **Audio**: SDL_mixer integration for sound and music playback
- **UI**: ImGui-based editor GUI with docking support
- **Transform**: 2D transform system with hierarchical parent-child relationships

### Editor
- **Visual Editor**: ImGui-based editor with multiple docking windows
- **Entity Inspector**: Browse and inspect entities organized by system
- **Property Editor**: Edit component properties in real-time
- **Layer Manager**: Manage and preview render layers
- **Control Bar**: Play/pause/stop game simulation controls

### Serialization
- **YAML Support**: Scene and entity serialization/deserialization via yaml-cpp
- **Custom Serializers**: Extensible serialization framework for custom components
- **Scene Management**: Load, save, and switch between scenes

## Architecture Overview

### Application Structure
The engine is organized into several key components:

```
HotBeanEngine/
├── include/             # Public API headers
│   └── HotBeanEngine/
│       ├── application/ # Application and manager interfaces
│       ├── core/        # Core ECS and type definitions
│       ├── defaults/    # Default components and systems
│       └── editor/      # Editor GUI interfaces
├── src/                 # Implementation files
│   ├── application/     # Application and manager implementations
│   ├── defaults/        # Default systems and components
│   ├── editor/          # Editor GUI implementation
│   └── unit_tests/      # Comprehensive test suite
└── docs/                # Documentation and Doxygen configuration
```

### Core Managers
- **EntityManager**: Handles entity creation, destruction, and lifecycle
- **ComponentManager**: Manages component registration and entity-component associations
- **SystemManager**: Registers, orders, and dispatches systems
- **ECSManager**: Coordinates between entity, component, and system managers
- **SceneManager**: Manages scene loading and switching
- **GameLoopManager**: Controls game loop state (Playing, Paused, Stopped)
- **LoggingManager**: Application-wide logging with file and console output

### Component System
All components derive from `IComponent` and optionally implement:
- `IMemberChanged`: For notifying changes to component members
- `IPropertyRenderable`: For editing properties in the editor
- `IName`: For identifying components by name

## Building the Engine

### Requirements
- CMake 3.20+
- C++20 compatible compiler
- SDL3, SDL3_image, SDL3_mixer, SDL3_ttf
- Box2D physics engine
- yaml-cpp for serialization
- ImGui for editor GUI
- Catch2 for unit tests

### Build Instructions
```bash
# Configure the project
cmake -S . -B build

# Build the engine and example game
cmake --build build

# Run the example game
./build/Game/Game
```

### Running Tests
```bash
cd build
ctest --output-on-failure
```

## Getting Started

### Creating a Custom Game
1. Extend the `Application` class
2. Create custom scenes inheriting from `DefaultScene`
3. Register custom components and systems
4. Load scenes and manage game state

### Creating Custom Components
```cpp
#include <HotBeanEngine/core/component.hpp>

class CustomComponent : public HBE::Core::IComponent {
public:
    int myValue = 0;
    
    static std::string_view StaticGetName() { return "CustomComponent"; }
    void Serialize(YAML::Node& node) const override { /* ... */ }
    void Deserialize(const YAML::Node& node) override { /* ... */ }
};
```

### Creating Custom Systems
```cpp
#include <HotBeanEngine/core/isystem.hpp>

class CustomSystem : public HBE::Core::ISystem {
public:    
    void OnUpdate() override {
        // System logic here
    }
};
```

## Configuration

The engine reads a `config.yaml` file at startup to configure:
- Window dimensions and title
- Logging level (DEBUG, INFO, WARNING, ERROR)
- Console logging enable/disable
- Physics settings (gravity, time step)

Example `config.yaml`:
```yaml
window:
  width: 1920
  height: 1080
  title: "My Game"

logging:
  level: INFO
  console: true

physics:
  gravity: 9.8
  timestep: 0.016667
```

## Documentation Structure

This documentation is organized as follows:

- **Classes**: Browse all ECS managers, components, and systems
- **Files**: View source files with Doxygen comments
- **Examples**: See the example game implementation in `Game/src/`
- **Related Pages**: Access additional guides and reference material

## Development Workflow

### Code Style
- Follow modern C++20 practices
- Use clang-format for consistent formatting
- Include comprehensive Doxygen comments
- Write unit tests for new functionality

### Tasks
- Format code: Run the "Format All C++ Files" VS Code task
- Generate documentation: Run the "Generate Doxygen Documentation" task
- Run tests: Execute `ctest` in the build directory

## Performance Considerations

- **Sparse Sets**: Provides cache-friendly component storage
- **Signature Filtering**: Minimizes entity iteration within systems
- **Fixed Timestep Physics**: Ensures deterministic physics simulation
- **Layer-Based Rendering**: Enables efficient render ordering and culling

## Contributing

When contributing to Hot Bean Engine:
1. Maintain the ECS architecture principles
2. Add Doxygen comments to all public APIs
3. Include unit tests for new features
4. Follow the established code style
5. Update documentation as needed

## Future Enhancements

- 3D rendering support
- Advanced physics features (joints, constraints)
- Particle system
- Tilemap support
- Animation framework
- Sound effect pooling and management
- Network multiplayer support
- Asset hot-reloading
- Visual scripting editor

## License

Hot Bean Engine is created for educational and development purposes.

## Contact & Support

For questions, issues, or contributions, please refer to the project repository and documentation.

---

**Current Version**: 0.0.1  
**Last Updated**: January 2026
