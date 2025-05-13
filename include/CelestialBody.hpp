#ifndef CELESTIAL_BODY_HPP
#define CELESTIAL_BODY_HPP

#include <SDL3/SDL.h>
#include <iostream>

#include "Vec2.hpp"
#include "Window.hpp"
#include "SimulationConfig.hpp"

class CelestialBody{

public:
    CelestialBody(double r, double x, double y, double mass, SDL_Color color);
    ~CelestialBody();

    void SetVelocity(const Vec2 vel);
    void ApplyGravity(const CelestialBody &b, double deltaTime);
    void Update(double deltaTime);
    void Draw(Window &win);

private:

    double m_radius;
    double m_mass;
    Vec2 m_position;
    Vec2 m_velocity;
    Vec2 m_screenCoordinates;

    SDL_Color m_color;

};

#endif 