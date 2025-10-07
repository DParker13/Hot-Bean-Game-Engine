# Hot Bean Engine

A 2D video game engine built using C++ and SDL2.

The Hot Bean Engine (Name Pending) is a personal project I've been working on to teach myself C++. This project is aimed at creating a lightweight and flexible game engine for 2D games. The engine is designed to be easy to use and extend, with a focus on performance and compatibility.

Based on Austin Morlan's simple ECS design from his blog post at https://austinmorlan.com/posts/entity_component_system/

## Features
------------

* 2D rendering using SDL2 (Soon to be upgraded to SDL3)
* Entity-Component-System (ECS) architecture
* Support for input, audio, physics, and rendering textures/sprites
* Basic game object management
* Scene management
* Easily expandable Components and Systems for game needs 

## Build and Run
-------------------

### Build Requirements
- C++ >= 17.0
- CMake >= 3.18

### Step 1: Clone the repository
```bash
git clone https://github.com/DParker13/Hot-Bean-Game-Engine.git
```

### Step 2: Create a build folder within the root project and navigate to it
```bash
mkdir build
cd build
```

### Step 3: Configure the project
```bash
cmake ..
```

### Step 4: Build the project
```bash
cd ..
cmake --build .
```

### Step 5: Run the example application
```bash
./Game.exe
```

## License
------------
The Hot Bean Engine is licensed under the MIT License.

## Contributing
------------
Contributions are welcome! If you'd like to help with the project, please fork the repository and submit a pull request.
