# Hot Bean Engine – AI Guide

## **Core Architecture**
- **ECS Pattern**: Austin Morlan sparse-set design with `Entity` (Uint64), `Component` (abstract type), `System` (generic processing). Limits: `MAX_ENTITIES=50,000`, `MAX_COMPONENTS=64` ([HotBeanEngine/include/HotBeanEngine/core/config.hpp](HotBeanEngine/include/HotBeanEngine/core/config.hpp)).
- **Managers**: Located in [HotBeanEngine/include/HotBeanEngine/application/managers](HotBeanEngine/include/HotBeanEngine/application/managers), wired by singleton `Application` ([HotBeanEngine/include/HotBeanEngine/application/application.hpp](HotBeanEngine/include/HotBeanEngine/application/application.hpp)). Key managers: `ECSManager` (facade), `EntityManager` (IDs/recycling), `ComponentManager` (sparse-set + name maps), `SystemManager` (registration/dispatch), `SceneManager` (scene loading/switching), `StateManager` (play/pause/stop + reload flag), `RenderManager`, `CameraManager`, `TransformManager`, `AudioManager`, `EventManager`, `LoggingManager` (with level filtering).
- **Application Lifecycle**: `Application()` loads config, creates logging, window/renderer, and managers, then initializes SDL, the editor GUI, and component listeners. `Start()` runs SDL event polling with a fixed-step physics accumulator (0.01s) and the usual `OnStart`/`OnPreEvent`/`OnEvent`/`OnWindowResize`/`OnFixedUpdate`/`OnUpdate`/`OnRender`/`OnPostRender` phases; in headless mode the `NoopEditorGUI` path auto-queues `Playing`.

## **Game Loop & State**
- **Flow**: Game loop in `Application::Start()` ([HotBeanEngine/src/application/application.cpp](HotBeanEngine/src/application/application.cpp)). State control via `StateManager`: queue `Playing`/`Paused`/`Stopped`, and when entering `Playing` from `Stopped` the current scene is reloaded through `ShouldReloadScene()`/`ClearReloadFlag()`.
- **Physics**: Fixed-step 0.01s timestep with accumulator pattern; Box2D integration via `PhysicsSystem`.

## **Component & System Conventions**
- **Components**: Inherit `IComponent`, optionally also `DirtyFlag` and `IPropertyRenderable`. Use `DEFINE_NAME("ComponentName")` macro. Implement `Serialize(YAML::Emitter&)` and `Deserialize(YAML::Node&)` for persistence. Register in `DefaultComponentFactory::RegisterComponents()` and `CreateComponentFromYAML()` ([HotBeanEngine/src/defaults/default_component_factory.cpp](HotBeanEngine/src/defaults/default_component_factory.cpp)). Example: `Transform2D` ([HotBeanEngine/include/HotBeanEngine/defaults/components/miscellaneous/transform_2d.hpp](HotBeanEngine/include/HotBeanEngine/defaults/components/miscellaneous/transform_2d.hpp)).
- **Systems**: Inherit `GameSystem<Component1, Component2, ...>` (auto-sets required signature). Use `DEFINE_NAME()` macro. Implement optional hooks: `OnStart()`, `OnPreEvent()`, `OnEvent()`, `OnWindowResize()`, `OnFixedUpdate()`, `OnUpdate()`, `OnRender()`, `OnPostRender()`. Register engine-wide systems in [HotBeanEngine/src/factories/system_factory.cpp](HotBeanEngine/src/factories/system_factory.cpp); the current default order is `PlayerControllerSystem`, `PhysicsSystem`, `CollisionSystem`, `ShapeSystem`, `TextSystem`, `InteractSystem`. `SystemManager` enforces membership and ordering ([HotBeanEngine/include/HotBeanEngine/application/managers/system_manager.hpp](HotBeanEngine/include/HotBeanEngine/application/managers/system_manager.hpp)).

## **Scene & Serialization**
- **Scenes**: Derive from `HBE::Application::Scene` ([HotBeanEngine/include/HotBeanEngine/application/scene.hpp](HotBeanEngine/include/HotBeanEngine/application/scene.hpp)) or `HBE::Core::IScene` for custom serialization/lifecycle control. `IScene` stores the scene name, path, and serialized scene file list. Use `SetupScene()` for scene setup and `CleanupScene()` for teardown; the example scene also unsubscribes event handlers in cleanup.
- **Serialization**: Scenes are serialized through the current scene serializer stack and the concrete `Scene` wrapper writes `Name` and `ScenePath` ([HotBeanEngine/src/application/scene.cpp](HotBeanEngine/src/application/scene.cpp)). YAML project files list scene paths, and `ProjectManager` loads those scenes into `SceneManager` during project open/startup. The build copies `Example Project/` into the build tree, not a `Game/` folder.
- **Project Management**: `ProjectManager` ([HotBeanEngine/src/editor/managers/project_manager.cpp](HotBeanEngine/src/editor/managers/project_manager.cpp)) handles project creation, loading, persistence, and startup project wiring. `CreateNewProject(const Project& project)` normalizes the filename, creates `assets/fonts`, `assets/music`, and `assets/sprites`, saves the project YAML, then updates `config.yaml` with the new `startup_path`.

## **Editor & UI**
- **Framework**: ImGui with SDL3 renderer, docking enabled. Dark theme with rounded corners and teal accents ([HotBeanEngine/src/editor/editor_gui.cpp](HotBeanEngine/src/editor/editor_gui.cpp)).
- **Architecture**: `IEditorGUI` interface (or `NoopEditorGUI` for headless); concrete `EditorGUI` class. Initialized post-Application via `EditorGUI::InitEditorGUI()`. Windows stored in `std::map<std::string, std::shared_ptr<IWindow>>` for O(1) lookup; each window has `m_menu_item_visible` flag.
- **Windows**: In [HotBeanEngine/src/editor/windows](HotBeanEngine/src/editor/windows). Key: `ConsoleWindow` (logs with DEBUG/INFO/WARNING/ERROR/FATAL filtering), `EntityWindow` (browse/select entities), `LayerWindow` (texture preview), `PropertyWindow` (component editing via `IPropertyRenderable`), `ProjectWindow`, `SceneWindow`, `ConfigWindow`, and `NewProjectWindow`.
- **Menu**: File (New/Open/Exit), Scene, Windows visibility. ControlBar: Start/Pause/Stop buttons (disabled if no scene loaded).
- **Dialogs**: SDL file/folder helpers in `EditorUtils` ([HotBeanEngine/src/editor/editor_utils.hpp](HotBeanEngine/src/editor/editor_utils.hpp)) with callback pattern.

## **Config & Globals**
- **Config Structure** ([HotBeanEngine/include/HotBeanEngine/core/config.hpp](HotBeanEngine/include/HotBeanEngine/core/config.hpp)): YAML with Project section (startup_path), Logging section (directory, level: DEBUG=0/INFO=1/WARNING=2/ERROR=3/FATAL=4, console flag). Auto-created at `./config.yaml` with defaults if missing.
- **Globals & Macros** ([HotBeanEngine/include/HotBeanEngine/application/macros.hpp](HotBeanEngine/include/HotBeanEngine/application/macros.hpp)): `g_app` (Application singleton), `g_ecs` (ECSManager), `LOG(type, message)` routes to LoggingManager with file/line/function info.

## **Build & Testing**
- **Dependencies**: CMake 3.18+ with FetchContent and C++20: SDL3, SDL3_image, SDL3_mixer, SDL3_ttf, Box2D, yaml-cpp, glm, ImGui, Catch2.
- **Build**: `cmake -S . -B build && cmake --build build` from repo root. The main executable target is `HotBeanEngine`; on the current Linux/Ninja layout it lands at `build/HotBeanEngine/src/HotBeanEngine`. Post-build copies `Example Project/` and `HotBeanEngine/assets/` into the build tree.
- **Tests**: Unit tests in [HotBeanEngine/src/unit_tests](HotBeanEngine/src/unit_tests) using Catch2. Target: `HotBeanEngine_Managers_Test`. Run: `ctest --output-on-failure` from build dir.
- **Tasks**: VS Code "Format All C++ Files" (clang-format), "Generate Doxygen Documentation" (outputs to `HotBeanEngine/docs`).

## **Extension Points**
- **Add Component**: Create header in `HotBeanEngine/include/HotBeanEngine/defaults/components/...`, implement `Serialize`/`Deserialize`, add to `DefaultComponentFactory::RegisterComponents()` and `CreateComponentFromYAML()`.
- **Add System**: Create in `HotBeanEngine/include/HotBeanEngine/systems/...`, inherit `GameSystem<Components...>`, register it in `HotBeanEngine/src/factories/system_factory.cpp` for engine-wide behavior.
- **Add Scene**: Derive from `HBE::Application::Scene`, implement `SetupScene()` and `CleanupScene()`, and register/load it through project/scene management.
- **Add Editor Window**: Create `IWindow` subclass in `HotBeanEngine/src/editor/windows/`, add to `EditorGUI::m_windows` map with unique name.
- **Add Config Value**: Update `config.hpp` globals, extend YAML load/save in `LoadConfig()`/`SaveConfig()`.

## **Running**
- **Executable**: `./build/HotBeanEngine/src/HotBeanEngine` from the repo root. Ensure the audio device is available and that the build tree contains the copied `Example Project/` and assets. Errors surface via `LoggingManager` (console + file) and SDL dialogs.
- **Example Project**: `Example Project/scenes/example_scene.cpp` demonstrates scene-local setup and cleanup with `HBE::Application::Scene`, including event subscriptions and component-driven interactions.
