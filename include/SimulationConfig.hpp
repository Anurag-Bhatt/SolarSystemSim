#ifndef SIMULATION_HPP
#define SIMULATION_HPP

inline constexpr double distanceScale = 1.0 / 1e6;     // 1 unit = 1,000,000 meters
inline constexpr double massScale = 1.0 / 1e24;        // 1 unit = 1e24 kg
inline constexpr double G = 6.67430e-11;
inline constexpr double scaledG = (G * massScale) / (distanceScale * distanceScale * distanceScale);
inline constexpr int accelScale = 800;

#endif