# CPlusEngine

CPlusEngine is a lightweight 2D game engine written in C++, created to explore engine architecture, modular design, and low-level game development using SDL3.

The project emphasizes a clear separation between core engine systems and game-specific code, making it suitable for small games, prototypes, and technical experimentation.

---

## Overview

CPlusEngine provides a compact but functional foundation for 2D games. It handles rendering, input, audio, and scene flow through a structured SDL3-based game loop, with a strong focus on clarity, maintainability, and learning rather than full production scope.

---

## Features

- Cross-platform support (Windows, macOS, Linux)
- SDL3-based rendering, input handling, and audio playback
- Clear separation between engine code and game logic
- Sprite system supporting static, animated, and moving sprites
- Scene management for organizing game states and transitions
- Audio system for music and sound effects
- TrueType font rendering via SDL3_ttf

---

## Requirements

- CMake 3.20 or newer
- C++17 compatible compiler (GCC, Clang, MSVC)
- SDL3
- SDL3_image
- SDL3_ttf

---

## Installing Dependencies

### Ubuntu / Debian

```bash
sudo apt-get install cmake build-essential libsdl3-dev libsdl3-image-dev libsdl3-ttf-dev
```

### macOS (Homebrew)

```bash
brew install cmake sdl3 sdl3_image sdl3_ttf
```

### Windows

Download the SDL3 development libraries from [https://www.libsdl.org/](https://www.libsdl.org/)

---

## Building the Project

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```

---

## Running

```bash
./build/bin/CPlusEngine
```

---

## Development Workflow

### Rebuild after making changes:

```bash
cmake --build build -j
```

### Clean rebuild:

```bash
rm -rf build
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```

---

## Project Structure

```
CPlusEngine/
├── engine/             # Engine source and headers
│   ├── include/
│   │   ├── core/       # Window, renderer, game loop
│   │   ├── graphics/   # Sprites, animations, text rendering
│   │   ├── audio/      # Audio system
│   │   ├── input/      # Input handling
│   │   └── scene/      # Scene management
│   └── src/            # Engine implementation
├── game/               # Game-specific code
│   ├── include/
│   └── src/
├── assets/             # Images, sounds, fonts
│   └── ...
└── CMakeLists.txt      # Build configuration
```

---

## Creating a Game with the Engine

1. Create a new game class in `game/include/`
2. Implement the game logic in `game/src/`
3. Connect your game in `main.cpp`
4. Add assets to the `assets/` directory
5. Build and run the project

---

## License

This project is released under the MIT License.

See the LICENSE file for details.

---

## Notes

This engine was created as a learning project to gain a deeper understanding of game engine structure, SDL3 workflows, and low-level C++ systems.
