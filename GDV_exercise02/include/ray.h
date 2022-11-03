#ifndef RAY_H
#define RAY_H

#include "common.h"
#include <limits>

struct Ray {
    Point3D origin;
    Vector3D direction;

    float t_min{epsilon};
    float t_max{std::numeric_limits<float>::infinity()};
};

struct IntersectionRay final : public Ray {
    // component-wise inverse of ray direction for faster intersection tests
    const Vector3D inv_direction{1.0f / direction.x, 1.0f / direction.y, 1.0f / direction.z};
    // allow implicit conversion from basic ray
    IntersectionRay(const Ray& r) : Ray{r} {}
};

#endif // !RAY_H