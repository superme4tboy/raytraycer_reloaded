#pragma once

#include "vec3.h"

class Ray
{

public:
    Ray(const vec3 &origin, const vec3 &direction)
        : m_origin(origin), m_direction(vec3::normalize(direction)) {}
    Ray() : m_origin(vec3(0.0)), m_direction(vec3(0.0)) {}

    vec3 origin() const { return m_origin; }

    vec3 direction() const { return m_direction; }

    vec3 at(double t) const
    {
        return m_origin + t * m_direction;
    }

    
private:
    vec3 m_origin;
    vec3 m_direction;
};
