#ifndef SIMULATION_HPP
#define SIMULATION_HPP

const double distanceScale = 1.0 / 1e6;     // 1 unit = 1,000,000 meters
const double massScale = 1.0 / 1e24;        // 1 unit = 1e24 kg
const double G = 6.67430e-11;
const double scaledG = (G * massScale) / (distanceScale * distanceScale * distanceScale);
const int accelScale = 800;


#endif