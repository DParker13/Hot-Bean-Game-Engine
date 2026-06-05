# Hot Bean Engine – AI Guide

## **Core Architecture**
- **ECS Pattern**: Austin Morlan sparse-set design with `Entity` (Uint64), `Component` (abstract type), `System` (generic processing). Limits: `MAX_ENTITIES=50,000`, `MAX_COMPONENTS=64` ([HotBeanEngine/include/HotBeanEngine/core/config.hpp](HotBeanEngine/include/HotBeanEngine/core/config.hpp)).
- **Managers**: Located in [HotBeanEngine/include/HotBeanEngine/application/managers](HotBeanEngine/include/HotBeanEngine/application/managers), wired by singleton `Application` ([HotBeanEngine/include/HotBeanEngine/application/application.hpp](HotBeanEngine/include/HotBeanEngine/application/application.hpp)). Key managers: `ECSManager` (facade), `EntityManager` (IDs/recycling), `ComponentManager` (sparse-set + name maps), `SystemManager` (registration/dispatch), `SceneManager` (scene loading/switching), `ApplicationStateManager` (play/pause/stop), `RenderManager`, `CameraManager`, `TransformManager`, `AudioManager`, `EventManager`, `LoggingManager` (with level filtering).
- **Application Lifecycle**: `Application()` initializes with `IComponentFactory` and `IEditorGUI`; `config.yaml` auto-created if missing. `Start()` runs: SDL event polling → fixed-step physics (0.01s accumulator) → OnStart/OnPreEvent/OnEvent/OnWindowResize/OnFixedUpdate/OnUpdate/OnRender/OnPostRender phases.

## **Game Loop & State**
- **Flow**: Game loop in `Application::Start()` ([HotBeanEngine/src/application/application.cpp](HotBeanEngine/src/application/application.cpp)). State control via `ApplicationStateManager`: `PlayGame()`/`PauseGame()`/`StopGame()` with reload flagging.
- **Physics**: Fixed-step 0.01s timestep with accumulator pattern; Box2D integration via `PhysicsSystem`.

## **Component & System Conventions**
- **Components**: Inherit `IComponent`, optionally also `DirtyFlag` and `IPropertyRenderable`. Use `DEFINE_NAME("ComponentName")` macro. Implement `Serialize(YAML::Emitter&)` and `Deserialize(YAML::Node&)` for persistence. Register in `DefaultComponentFactory::RegisterComponents()` and `CreateComponentFromYAML()` ([HotBeanEngine/src/defaults/default_component_factory.cpp](HotBeanEngine/src/defaults/default_component_factory.cpp)). Example: `Transform2D` ([HotBeanEngine/include/HotBeanEngine/defaults/components/miscellaneous/transform_2d.hpp](HotBeanEngine/include/HotBeanEngine/defaults/components/miscellaneous/transform_2d.hpp)).
- **Systems**: Inherit `GameSystem<Component1, Component2, ...>` (auto-sets required signature). Use `DEFINE_NAME()` macro. Implement optional hooks: `OnStart()`, `OnPreEvent()`, `OnEvent()`, `OnWindowResize()`, `OnFixedUpdate()`, `OnUpdate()`, `OnRender()`, `OnPostRender()`. Register via `g_ecs.RegisterSystem<MySystem>()` in scene's `SetupDefaultSystems()`. `SystemManager` enforces membership and ordering ([HotBeanEngine/include/HotBeanEngine/application/managers/system_manager.hpp](HotBeanEngine/include/HotBeanEngine/application/managers/system_manager.hpp)).

## **Scene & Serialization**
- **Scenes**: Derive from `HBE::Core::Scene`; default is `DefaultScene` ([HotBeanEngine/include/HotBeanEngine/defaults/default_scene.hpp](HotBeanEngine/include/HotBeanEngine/defaults/default_scene.hpp)). Setup systems in `SetupDefaultSystems()` method; registered systems applied in order (TransformSystem → CameraSystem → PhysicsSystem → CollisionSystem → ShapeSystem → TextSystem → InteractSystem → PlayerControllerSystem → InputEventListener → Audio).
- **Serialization**: Via `DefaultSceneSerializer` ([HotBeanEngine/src/defaults/default_scene_serializer.cpp](HotBeanEngine/src/defaults/default_scene_serializer.cpp)). YAML format: walk all entities → serialize components recursively. Parent-child relationships tracked via `Transform2D::m_parent`; deserialization uses component factory to reconstruct. YAML files in `Game/src/scenes/*.yaml` auto-copied to build output.
- **Project Management**: `ProjectManager` ([HotBeanEngine/src/editor/project_manager.hpp](HotBeanEngine/src/editor/project_manager.hpp)) handles project creation, loading, persistence. `CreateNewProject(const Project& project)` takes a copy, applies filename normalization (e.g., "New Project" → "new_project.yaml"), saves YAML with project metadata. Startup project path loaded from `config.yaml` Project.startup_path.

## **Editor & UI**
- **Framework**: ImGui with SDL3 renderer, docking enabled. Dark theme with rounded corners and teal accents ([HotBeanEngine/src/editor/editor_gui.cpp](HotBeanEngine/src/editor/editor_gui.cpp)).
- **Architecture**: `IEditorGUI` interface (or `NoopEditorGUI` for headless); concrete `EditorGUI` class. Initialized post-Application via `EditorGUI::InitEditorGUI()`. Windows stored in `std::map<std::string, std::shared_ptr<IWindow>>` for O(1) lookup; each window has `m_menu_item_visible` flag.
- **Windows**: In [HotBeanEngine/src/editor/windows](HotBeanEngine/src/editor/windows). Key: `ConsoleWindow` (logs with DEBUG/INFO/WARNING/ERROR/FATAL filtering), `EntityWindow` (browse/select entities), `LayerWindow` (texture preview), `PropertyWindow` (component editing via `IPropertyRenderable`), `NewProjectWindow` (project creation with folder dialog).
- **Menu**: File (New/Open/Exit), Scene (Load), Windows visibility. ControlBar: Start/Pause/Stop buttons (disabled if no scene loaded).
- **Dialogs**: SDL file/folder helpers in `EditorUtils` ([HotBeanEngine/src/editor/editor_utils.hpp](HotBeanEngine/src/editor/editor_utils.hpp)) with callback pattern.

## **Config & Globals**
- **Config Structure** ([HotBeanEngine/include/HotBeanEngine/core/config.hpp](HotBeanEngine/include/HotBeanEngine/core/config.hpp)): YAML with Project section (startup_path), Logging section (path, level: DEBUG=0/INFO=1/WARNING=2/ERROR=3/FATAL=4, console flag). Auto-created at `./config.yaml` with defaults if missing.
- **Globals & Macros** ([HotBeanEngine/include/HotBeanEngine/application/macros.hpp](HotBeanEngine/include/HotBeanEngine/application/macros.hpp)): `g_app` (Application singleton), `g_ecs` (ECSManager), `LOG(type, message)` routes to LoggingManager with file/line/function info.

## **Build & Testing**
- **Dependencies**: CMake 3.11+ with FetchContent: SDL3, SDL3_image, SDL3_mixer, SDL3_ttf, Box2D, yaml-cpp, glm, ImGui, Catch2.
- **Build**: `cmake -S . -B build && cmake --build build` from repo root. Executable at `build/Game/Game`. Post-build copies `config.yaml`, `assets/`, `scenes/` to build output.
- **Tests**: Unit tests in [HotBeanEngine/src/unit_tests](HotBeanEngine/src/unit_tests) using Catch2. Target: `HotBeanEngine_Managers_Test`. Run: `ctest --output-on-failure` from build dir.
- **Tasks**: VS Code "Format All C++ Files" (clang-format), "Generate Doxygen Documentation" (outputs to `HotBeanEngine/docs`).

## **Extension Points**
- **Add Component**: Create header in `HotBeanEngine/include/HotBeanEngine/defaults/components/...`, implement `Serialize`/`Deserialize`, add to `DefaultComponentFactory::RegisterComponents()` and `CreateComponentFromYAML()`.
- **Add System**: Create in `HotBeanEngine/include/HotBeanEngine/defaults/systems/...`, inherit `GameSystem<Components...>`, register in scene's `SetupDefaultSystems()`.
- **Add Editor Window**: Create `IWindow` subclass in `HotBeanEngine/src/editor/windows/`, add to `EditorGUI::m_windows` map with unique name.
- **Add Config Value**: Update `config.hpp` globals, extend YAML load/save in `LoadConfig()`/`SaveConfig()`.

## **Running**
- **Executable**: `./build/Game/Game` (ensure working audio device and that config/assets/scenes were copied). Errors surface via `LoggingManager` (console + file) and SDL dialogs.
- **Example Game**: `Game::ExampleGame` ([Game/src/game/example_game.cpp](Game/src/game/example_game.cpp)) extends `Application`, constructs `DefaultSceneSerializer`, registers/loads `ExampleScene` from YAML.
