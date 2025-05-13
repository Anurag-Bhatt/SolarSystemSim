#include "../include/CelestialBody.hpp"

CelestialBody::CelestialBody(double r, double x, double y, double mass, SDL_Color color)
: m_radius(r), m_position(x, y), m_mass(mass), m_color(color), m_velocity(0, 0) {}

CelestialBody::~CelestialBody() {}

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
}

void CelestialBody::Draw(Window &win)
{
    // Convert simulation coordinates to screen coordinates
    m_screenCoordinates.x = static_cast<int>(m_position.x + win.screenCenter.x);
    m_screenCoordinates.y = static_cast<int>(m_position.y + win.screenCenter.y);

    // Set drawing color
    SDL_SetRenderDrawColor(win.getRenderer(), 
                          m_color.r, m_color.g, m_color.b, m_color.a);

    // Draw circle using multiple points
    for (int angle = 0; angle < 360; ++angle) {
        double radians = angle * M_PI / 180.0;
        int x = static_cast<int>(m_screenCoordinates.x + m_radius * std::cos(radians));
        int y = static_cast<int>(m_screenCoordinates.y + m_radius * std::sin(radians));
        SDL_RenderPoint(win.getRenderer(), x, y);
    }
}