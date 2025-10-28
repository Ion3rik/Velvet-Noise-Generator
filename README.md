# Velvet Noise Generator

A velvet noise generator plugin

---

## GUI Controls

- Gain – Output Volume in dB
- Density – Pulses/s
- Pulse Width – Width of each velvet pulse in percentage of the grid size
- Regularity – Regularity of the pulse placement and signs (0 = fully random, 1 = fully regular)

---
## Downloads

### macOS Universal Binary
- VST3 + AU + Standalone included
- Works on Intel and Apple Silicon Macs
- [Download VelvetNoiseGenerator v0.1 (macOS)](https://github.com/Ion3rik/Velvet-Noise-Generator/releases/download/v0.1/VelvetNoiseGenerator-v0.1-mac.zip)

---

## Build Requirements

- C++17 compiler (Clang, GCC, MSVC)  
- CMake 3.21+
- Ninja (optional but recommended)  

---

## Setup

Clone the repository:

```bash
git clone --recurse-submodules https://github.com/Ion3rik/Velvet-Noise-Generator.git
cd Velvet-Noise-Generator
```

## Configure and Build

```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
ninja -C build
```

