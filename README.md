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
../bin/SolarSystemSim
```
## Controls

You can interact with the Solar System Simulation in real-time using the following controls:

### Keyboard

| Key         | Action                         |
|-------------|--------------------------------|
| `W`         | Pan up                         |
| `A`         | Pan left                       |
| `S`         | Pan down                       |
| `D`         | Pan right                      |
| `P`         | Pause / Resume the simulation  |
| `→ (Right Arrow)` | Double simulation speed     |
| `← (Left Arrow)`  | Halve simulation speed      |
| `ESC`       | Exit the simulation            |

> Panning is relative to the current zoom level — higher zoom means smoother movement.

### Mouse

| Input       | Action                         |
|-------------|--------------------------------|
| Scroll Up   | Zoom in                        |
| Scroll Down | Zoom out                       |

> Zooming scales the view smoothly, giving you a closer or wider look at the solar system.

---

Feel free to tweak the pan/zoom speed constants in the source if you want a different feel!
