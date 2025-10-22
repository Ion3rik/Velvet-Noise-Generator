# Audio Plugin Template

A minimal template for creating audio plugins with JUCE and CMake.

---

## Features

- Cross-platform audio plugin template (VST3, AU, etc.)  
- CMake-based build system  

---

## Requirements

- C++17 compiler (Clang, GCC, MSVC)  
- CMake 3.21+
- Ninja (optional but recommended)  

---

## Setup

Clone the repository:

```bash
git clone --recurse-submodules https://github.com/Ion3rik/Audio-Plugin-Template.git
cd Audio-Plugin-Template
```

## Configure and Build

```bash
cmake -S . -B build -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
ninja -C build
```

