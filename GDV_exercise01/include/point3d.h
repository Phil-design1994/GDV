#pragma once

#include <algorithm> // std::min, std::max
#include <cmath> // std::sqrt
#include <ostream> // std::ostream

#include <nanogui/vector.h>

/**
 * @brief 3D point
 *
 * we define all of its operations in the header file
 * to allow the compiler to easily inline these simple operations
 */
struct Point3D {
    float x, y, z;

    /// initialize each member with a different value
    Point3D(float x, float y, float z) : x{x}, y{y}, z{z} {}
    /// initialize all members with the same value
    Point3D(float xyz = 0.0f) : Point3D{xyz, xyz, xyz} {}

    bool operator==(const Point3D& other) const = default;

    /// conversion from nanogui vector
    Point3D(const nanogui::Vector3f& v) : x{v.x()}, y{v.y()}, z{v.z()} {}
    /// conversion to nanogui vector
    operator nanogui::Vector3f() { return {x, y, z}; }

    void operator+=(const Point3D& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
    }
    Point3D operator+(const Point3D& other) const
    {
        Point3D copy{*this};
        copy += other;
        return copy;
    }

    void operator-=(const Point3D& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
    }
    Point3D operator-(const Point3D& other) const
    {
        Point3D copy{*this};
        copy -= other;
        return copy;
    }

    Point3D operator-() const
    {
        Point3D copy{*this};
        copy.x = -copy.x;
        copy.y = -copy.y;
        copy.z = -copy.z;
        return copy;
    }

    /// compute the component-wise multiplication
    void operator*=(const Point3D& other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
    }
    /// compute the component-wise multiplication
    Point3D operator*(const Point3D& other) const
    {
        Point3D copy{*this};
        copy *= other;
        return copy;
    }

    /// compute the component-wise division
    void operator/=(const Point3D& other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
    }
    /// compute the component-wise division
    Point3D operator/(const Point3D& other) const
    {
        Point3D copy{*this};
        copy /= other;
        return copy;
    }

    /// compute the L2 norm (the distance to [0.0, 0.0, 0.0])
    float norm() const { return std::sqrt(x * x + y * y + z * z); }

    float minComponent() const { return x < y ? (x < z ? x : z) : (y < z ? y : z); }

    float maxComponent() const { return x > y ? (x > z ? x : z) : (y > z ? y : z); }
};

/// compute the component-wise minimum
inline Point3D min(const Point3D& a, const Point3D& b)
{
    return {std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z)};
}

/// compute the component-wise maximum
inline Point3D max(const Point3D& a, const Point3D& b)
{
    return {std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z)};
}

/// compute the component-wise absolute
inline Point3D abs(const Point3D& a)
{
    return ::max(a, -a);
}

/// compute the dot product of a and b
inline float dot(const Point3D& a, const Point3D& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

/// compute the cross product of a and b
inline Point3D cross(const Point3D& a, const Point3D& b)
{
    return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

/// compute the normalized vector
inline Point3D normalize(const Point3D& p)
{
    float invNorm = 1.0f / p.norm();
    if (std::isinf(invNorm) || std::isnan(invNorm))
        return {};
    return p * invNorm;
}

/// compute the distance between a and b
inline float distance(const Point3D& a, const Point3D& b) { return (a - b).norm(); }

/// check if all components are less than the other point's components
inline bool operator<(const Point3D& a, const Point3D& b)
{
    return a.x < b.x && a.y < b.y && a.z < b.z;
}

/// check if all components are greater than the other point's components
inline bool operator>(const Point3D& a, const Point3D& b)
{
    return a.x > b.x && a.y > b.y && a.z > b.z;
}

/// check if all components are less than the other point's components or equal
inline bool operator<=(const Point3D& a, const Point3D& b)
{
    return a.x <= b.x && a.y <= b.y && a.z <= b.z;
}

/// check if all components are greater than the other point's components or equal
inline bool operator>=(const Point3D& a, const Point3D& b)
{
    return a.x >= b.x && a.y >= b.y && a.z >= b.z;
}

/// "to string"
inline std::ostream& operator<<(std::ostream& os, const Point3D& p)
{
    os << '[' << p.x << ", " << p.y << ", " << p.z << ']';
    return os;
}
