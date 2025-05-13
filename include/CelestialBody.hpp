#ifndef CELESTIAL_BODY_HPP
#define CELESTIAL_BODY_HPP

#include <SDL3/SDL.h>
#include <iostream>
#include <deque>

#include "Vec2.hpp"
#include "Window.hpp"
#include "SimulationConfig.hpp"

class CelestialBody{

public:
    CelestialBody(double r, double x, double y, double mass, SDL_Color color);
    CelestialBody(const std::string name, double r, double x, double y, double mass, SDL_Color color);
    ~CelestialBody();

    CelestialBody *CreatePlanet(const std::string& name, double radius, double distanceFromSunAU,
    double massInKg, SDL_Color color); 
    std::string getName();
    double getMass()const;
    void SetVelocity(const Vec2 vel);
    void ApplyGravity(const CelestialBody &b, double deltaTime);
    void Update(double deltaTime);
    void Draw(Window &win);

    friend std::ostream& operator<<(std::ostream& out, const CelestialBody& cb);

private:

    std::string m_bodyName;

    double m_radius;
    double m_mass;
    Vec2 m_position;
    Vec2 m_velocity;
    Vec2 m_screenCoordinates;

    SDL_Color m_color;

    int trailUpdateIntervalFrames = 5;
    int trailFrameCounter = 0;

    int maxTrailLength = 300;
    std::deque<Vec2> orbitTrail;

};

#endif 