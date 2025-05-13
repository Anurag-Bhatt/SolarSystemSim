#ifndef VEC2_HPP
#define VEC2_HPP

#include <iostream>
#include <cmath>

class Vec2 {
public:
    double x, y;

    Vec2(double x = 0.0f, double y = 0.0f);

    // Addition
    Vec2 operator+(const Vec2& other) const;

    // Subtraction
    Vec2 operator-(const Vec2& other) const;

    // Scalar multiplication
    Vec2 operator*(double scalar) const;

    // Scalar division
    Vec2 operator/(double scalar) const;

    // Compound assignment operators
    Vec2& operator+=(const Vec2& other);
    Vec2& operator-=(const Vec2& other);
    Vec2& operator*=(double scalar);
    Vec2& operator/=(double scalar);

    // Comparison operators
    bool operator==(const Vec2 other) const;
    bool operator==(const double other) const;

    // Magnitude
    double length() const;

    // Normalize the vector
    Vec2 normalized() const;

    // Dot product
    double dot(const Vec2& other) const;

    // Distance to another vector
    double distanceTo(const Vec2& other) const;

    // Debug print
    void print() const;

    // Friend for stream output
    friend std::ostream& operator<<(std::ostream& out, const Vec2& v);
};

#endif // VEC2_HPP
