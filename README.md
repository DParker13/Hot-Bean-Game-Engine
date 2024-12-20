# Hot Bean Engine
 Learning C++ and SDL by creating a 2D video game engine

```
HotBeanEngine
├─ .gitattributes
├─ .gitignore
├─ assets
│  └─ fonts
│     └─ LT_Superior_Mono
│        ├─ LTSuperiorMono-Bold.otf
│        ├─ LTSuperiorMono-Medium.otf
│        ├─ LTSuperiorMono-Regular.otf
│        ├─ LTSuperiorMono-Regular.ttf
│        ├─ LTSuperiorMono-Semibold.otf
│        └─ OFL.txt
├─ CMakeLists.txt
├─ docs
├─ include
│  └─ FastNoiseLite.h
├─ README.md
├─ src
│  ├─ application
│  │  ├─ application.cpp
│  │  └─ application.hpp
│  ├─ base
│  │  ├─ CMakeLists.txt
│  │  ├─ Controller.cpp
│  │  ├─ Controller.h
│  │  ├─ Entity.cpp
│  │  ├─ Entity.h
│  │  ├─ Player.cpp
│  │  ├─ Player.h
│  │  ├─ Text.cpp
│  │  └─ Text.h
│  ├─ components
│  │  ├─ CMakeLists.txt
│  │  ├─ player.hpp
│  │  ├─ rigidbody.hpp
│  │  ├─ text.hpp
│  │  └─ transform.hpp
│  ├─ core
│  │  ├─ CMakeLists.txt
│  │  ├─ component_manager.cpp
│  │  ├─ component_manager.hpp
│  │  ├─ core_manager.cpp
│  │  ├─ core_manager.hpp
│  │  ├─ ecs.hpp
│  │  ├─ entity_manager.cpp
│  │  ├─ entity_manager.hpp
│  │  ├─ sparse_set.hpp
│  │  ├─ system_manager.cpp
│  │  └─ system_manager.hpp
│  ├─ gameobjects
│  │  ├─ CMakeLists.txt
│  │  ├─ gameobject.hpp
│  │  ├─ player.hpp
│  │  └─ text.hpp
│  ├─ main.cpp
│  ├─ shared
│  │  ├─ CMakeLists.txt
│  │  ├─ EventSystem.h
│  │  ├─ Matrix.cpp
│  │  ├─ Matrix.h
│  │  ├─ Position.cpp
│  │  └─ Position.h
│  ├─ systems
│  │  ├─ CMakeLists.txt
│  │  ├─ input_system.cpp
│  │  ├─ input_system.hpp
│  │  ├─ physics_system.cpp
│  │  ├─ physics_system.hpp
│  │  ├─ player_controller_system.cpp
│  │  ├─ player_controller_system.hpp
│  │  ├─ render_system.cpp
│  │  ├─ render_system.hpp
│  │  ├─ ui_system.cpp
│  │  └─ ui_system.hpp
└─ TODO.txt

```