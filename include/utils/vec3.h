#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <algorithm>
#include "random.h"

class vec3 {
private:
    static Random random;
public:
    double x, y, z;

    // Constructors
    vec3();
    vec3(double x);
    vec3(double _x, double _y, double _z);

    // Methods
    double length() const;

    vec3 operator+(const vec3& other) const;

    vec3 operator-(const vec3& other) const;

    vec3 operator-() const;

    vec3 operator*(double scalar) const;

    vec3 operator*(const vec3& other) const;

    vec3 operator/(double scalar) const;

    vec3& operator+=(const vec3& other);

    vec3& operator+=(const double scalar);

    bool operator!=(const vec3& other) const;

    double length_squared() const;

    vec3 cross(const vec3& other) const;

    std::ostream &operator<<(std::ostream &os) const;

    void print() const;
    //remove later
    vec3 random_in_unit_sphere();
    vec3 random_unit_vector();
    static vec3 randomVec3();
    static vec3 randomVec3(double min, double max);
    //end remove later

    static double dot(const vec3& v, const vec3& other);
    static vec3 normalize(const vec3& v);
    static vec3 clamp(const vec3& v, double min, double max);
    static vec3 sqrt(const vec3 &vec);
};

using point3 = vec3;

vec3 operator*(double scalar, const vec3& v);

#endif 
