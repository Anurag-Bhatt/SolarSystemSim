#include "../include/CelestialBody.hpp"

#include <random>
#include <cmath>



CelestialBody::CelestialBody(double r, double x, double y, double mass, SDL_Color color)
: m_radius(r), m_position(x, y), m_mass(mass), m_color(color), m_velocity(0, 0) {}

CelestialBody::CelestialBody(const std::string name, double r, double x, double y, double mass, SDL_Color color)
:m_bodyName(name), m_radius(r), m_position(x, y), m_mass(mass), m_color(color), m_velocity(0, 0) {}


CelestialBody::~CelestialBody() {}

CelestialBody *CelestialBody::CreatePlanet(const std::string &name, double radius, double distanceFromSunAU, double massInKg, SDL_Color color)
{
    const CelestialBody &sun = *this;
    double distance = distanceFromSunAU * distanceScale * 149.6e6;
    double mass = massInKg * massScale;
    double velocity = sqrt(scaledG * sun.getMass() / distance) * 10 / distanceScale;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 2 * M_PI);
    double angle = dis(gen);

    // Calculate the coordinates
    double x = distance * std::cos(angle);
    double y = distance * std::sin(angle);

    auto* planet = new CelestialBody(name, radius, x, y, mass, color);
    planet->SetVelocity(Vec2(-velocity*std::sin(angle), velocity*std::cos(angle)));
    return planet;
}

std::string CelestialBody::getName()
{
    return m_bodyName;
}

double CelestialBody::getMass() const
{
    return m_mass;
}

void CelestialBody::SetVelocity(const Vec2 vel)
{
    m_velocity = vel;
}

void CelestialBody::ApplyGravity(const CelestialBody &b, double deltaTime)
{
    Vec2 direction = b.m_position - m_position;
    double distance = direction.length();
    
    if (distance > 0) {
        Vec2 normalizedDir = direction / distance;
        double forceMagnitude = (scaledG * m_mass * b.m_mass) / (distance * distance);
        Vec2 acceleration = normalizedDir * accelScale * (forceMagnitude / m_mass) / (distanceScale * distanceScale);
        m_velocity += acceleration * deltaTime;
    }
}

void CelestialBody::Update(double deltaTime)
{
    m_position += m_velocity * deltaTime * 10;

    trailFrameCounter++;
    if(trailFrameCounter > trailUpdateIntervalFrames){
        orbitTrail.push_back(m_position);
        trailFrameCounter = 0;
    }
     
    if(orbitTrail.size() > maxTrailLength){
        orbitTrail.pop_front();
    }

}

void CelestialBody::Draw(Window &win)
{
    // Convert simulation coordinates to screen coordinates
    m_screenCoordinates.x = static_cast<int>((m_position.x + win.panOffset.x) * win.zoom + win.screenCenter.x);
    m_screenCoordinates.y = static_cast<int>((m_position.y + win.panOffset.y) * win.zoom + win.screenCenter.y);
    int renderRadius = static_cast<int>(m_radius * win.zoom);
    // Set drawing color
    SDL_SetRenderDrawColor(win.getRenderer(), 
                          m_color.r, m_color.g, m_color.b, m_color.a);

    // Draw circle using multiple points
    for (int angle = 0; angle < 360; ++angle) {
        double radians = angle * M_PI / 180.0;
        int x = static_cast<int>(m_screenCoordinates.x + renderRadius * std::cos(radians));
        int y = static_cast<int>(m_screenCoordinates.y + renderRadius * std::sin(radians));
        SDL_RenderPoint(win.getRenderer(), x, y);
    }

    if(orbitTrail.size() > 1){
        for(size_t i = 1; i < orbitTrail.size(); i++){
            SDL_SetRenderDrawColor(win.getRenderer(), m_color.r, m_color.g, m_color.b, 100);
            
            double x1 = (orbitTrail[i - 1].x + win.panOffset.x) * win.zoom + win.screenCenter.x;
            double y1 = (orbitTrail[i - 1].y + win.panOffset.y) * win.zoom + win.screenCenter.y;

            double x2 = (orbitTrail[i].x + win.panOffset.x) * win.zoom + win.screenCenter.x;
            double y2 = (orbitTrail[i].y + win.panOffset.y) * win.zoom + win.screenCenter.y;

            SDL_RenderLine(win.getRenderer(), x1, y1, x2, y2);
        }
    }
}


std::ostream &operator<<(std::ostream &out, const CelestialBody &cb)
{
    out << cb.m_bodyName << " \n"
        << "Mass: " << cb.m_mass << " \n"
        << "Position: " << cb.m_position << " \n"
        << "Velocity: " << cb.m_velocity << std::endl;
    return out;
}