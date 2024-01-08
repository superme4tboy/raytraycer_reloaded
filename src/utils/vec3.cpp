#include "vec3.h"
#include <iostream>
#include <cmath>

// Constructors
vec3::vec3() : x(0.0), y(0.0), z(0.0) {}
vec3::vec3(double x) : x(x), y(x), z(x) {}
vec3::vec3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

// Methods
double vec3::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

double vec3::length_squared() const {
    return x * x + y * y + z * z;
}

vec3 vec3::operator+(const vec3& other) const {
    return vec3(x + other.x, y + other.y, z + other.z);
}

vec3& vec3::operator+=(const vec3& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

vec3& vec3::operator+=(const double scalar) {
    x += scalar;
    y += scalar;
    z += scalar;
    return *this;
}

vec3 vec3::operator-(const vec3& other) const {
    return vec3(x - other.x, y - other.y, z - other.z);
}

vec3 vec3::operator*(double scalar) const {
    return vec3(x * scalar, y * scalar, z * scalar);
}

vec3 vec3::operator*(const vec3& other) const {
    return vec3(x * other.x, y * other.y, z * other.z);
}

vec3 vec3::cross(const vec3& other) const {
    return vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

vec3 vec3::operator/(double scalar) const {
    return vec3(x / scalar, y / scalar, z / scalar);
}

std::ostream &vec3::operator<<(std::ostream &os) const {
    os << "(" << x << ", " << y << ", " << z << ")";
    return os;
}

vec3 vec3::normalize(const vec3& v) {
    double len = v.length();
    return vec3(v.x / len, v.y / len, v.z / len);
}

vec3 vec3::clamp(const vec3& v, double min, double max) {
    return vec3(std::clamp(v.x, min, max), std::clamp(v.y, min, max), std::clamp(v.z, min, max));
}

double vec3::dot(const vec3& v, const vec3& other) {
    return v.x * other.x + v.y * other.y + v.z * other.z;
}

vec3 vec3::sqrt(const vec3 &vec)
{
    double x = std::sqrt(vec.x);
    double y = std::sqrt(vec.y);
    double z = std::sqrt(vec.z);
    return vec3(x,y,z);
}

void vec3::print() const {
    std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}

vec3 operator*(double scalar, const vec3& v) {
    return vec3(scalar * v.x, scalar * v.y, scalar * v.z);
}





