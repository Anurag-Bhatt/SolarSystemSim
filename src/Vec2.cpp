#include "../include/Vec2.hpp"
#include <cmath>
#include <iostream>

Vec2::Vec2(double x, double y) : x(x), y(y) {}

Vec2 Vec2::operator+(const Vec2& other) const {
    return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator-(const Vec2& other) const {
    return Vec2(x - other.x, y - other.y);
}

Vec2 Vec2::operator*(double scalar) const {
    return Vec2(x * scalar, y * scalar);
}

Vec2 Vec2::operator/(double scalar) const {
    return Vec2(x / scalar, y / scalar);
}

Vec2& Vec2::operator+=(const Vec2& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vec2& Vec2::operator-=(const Vec2& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vec2& Vec2::operator*=(double scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

Vec2& Vec2::operator/=(double scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
}

bool Vec2::operator==(const Vec2 other) const {
    return x == other.x && y == other.y;
}

bool Vec2::operator==(const double other) const {
    return x == other && y == other;
}

double Vec2::length() const {
    return std::sqrt(x * x + y * y);
}

Vec2 Vec2::normalized() const {
    double len = length();
    if (len == 0) return Vec2(0, 0);
    return Vec2(x / len, y / len);
}

double Vec2::dot(const Vec2& other) const {
    return x * other.x + y * other.y;
}

double Vec2::distanceTo(const Vec2& other) const {
    return (*this - other).length();
}

void Vec2::print() const {
    std::cout << "(" << x << ", " << y << ")" << std::endl;
}

std::ostream& operator<<(std::ostream& out, const Vec2& v) {
    out << "(" << v.x << ", " << v.y << ")";
    return out;
}
