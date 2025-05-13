# SolarSystemSim

A simple solar system simulation using SDL3 and ImGui(WIP).
-
![Simulation Preview](assets/preview.png)
-
### Orbit Trails
![Preview_OrbitTrail](assets/preview_oribitTrail.png)

---
## Structure

- `bin/` - compiled binaries
- `build/` - intermediate build files
- `logs/` - simulation output logs
- `assets/` - shaders, textures, etc.
- `include/` - header files
- `src/` - source code
- `third_party/` - external libraries

## Build

Uses CMake to build.

```bash
mkdir -p build
cd build
cmake ..
make
```
