#include "vec3.h"
#include <iostream>
#include <cmath>

Random vec3::random = Random();

// Constructors
vec3::vec3() : x(0.0), y(0.0), z(0.0) {}
vec3::vec3(double x) : x(x), y(x), z(x) {}
vec3::vec3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

// Methods
double vec3::length() const
{
    return std::sqrt(x * x + y * y + z * z);
}

double vec3::length_squared() const
{
    return x * x + y * y + z * z;
}

vec3 vec3::operator+(const vec3 &other) const
{
    return vec3(x + other.x, y + other.y, z + other.z);
}

vec3 vec3::operator+=(const vec3 &other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

vec3 vec3::operator+=(const double scalar)
{
    x += scalar;
    y += scalar;
    z += scalar;
    return *this;
}

vec3 vec3::operator-(const vec3 &other) const
{
    return vec3(x - other.x, y - other.y, z - other.z);
}

vec3 vec3::operator-() const
{
    return vec3(-x, -y, -z);
}

vec3 vec3::operator*(double scalar) const
{
    return vec3(x * scalar, y * scalar, z * scalar);
}

vec3 vec3::operator*(const vec3 &other) const
{
    return vec3(x * other.x, y * other.y, z * other.z);
}

vec3 vec3::cross(const vec3 &other) const
{
    return vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

vec3 vec3::operator/(double scalar) const
{
    return vec3(x / scalar, y / scalar, z / scalar);
}

std::ostream &vec3::operator<<(std::ostream &os) const
{
    os << "(" << x << ", " << y << ", " << z << ")";
    return os;
}

bool vec3::operator!=(const vec3 &other) const
{
    return x != other.x || y != other.y || z != other.z;
}

vec3 vec3::normalize(const vec3 &v)
{
    double len = v.length();
    return vec3(v.x / len, v.y / len, v.z / len);
}

vec3 vec3::clamp(const vec3 &v, double min, double max)
{
    return vec3(std::clamp(v.x, min, max), std::clamp(v.y, min, max), std::clamp(v.z, min, max));
}
vec3 vec3::randomVec3()
{
    return vec3(random.getRandom(), random.getRandom(), random.getRandom());
}

vec3 vec3::randomVec3(double min, double max)
{
    Random randomMinMax = Random(min, max);
    return vec3(randomMinMax.getRandom(), randomMinMax.getRandom(), randomMinMax.getRandom());
}

vec3 vec3::random_in_unit_sphere()
{
    while (true)
    {
        auto p = vec3::randomVec3(-1, 1);
        if (p.length_squared() < 1)
            return p;
    }
}

vec3 vec3::random_unit_vector()
{
    return vec3::normalize(random_in_unit_sphere());
}

vec3 vec3::random_on_hemisphere(const vec3& normal) {
    vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}

bool vec3::near_zero() const
{
    // Return true if the vector is close to zero in all dimensions.
    const auto s = 1e-8;
    return (fabs(x) < s) && (fabs(y) < s) && (fabs(z) < s);
}

vec3 vec3::reflect(const vec3& normal) const {
    return *this - 2 * dot(*this, normal) * normal;
}

vec3 vec3::refract(const vec3& normal, double etai_over_etat) const {
    auto cos_theta = fmin(dot(-*this, normal), 1.0);
    vec3 r_out_perp = etai_over_etat * (*this + cos_theta * normal);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * normal;
    return r_out_perp + r_out_parallel;
}

double vec3::dot(const vec3 &v, const vec3 &other)
{
    return v.x * other.x + v.y * other.y + v.z * other.z;
}

vec3 vec3::sqrt(const vec3 &vec)
{
    double x = std::sqrt(vec.x);
    double y = std::sqrt(vec.y);
    double z = std::sqrt(vec.z);
    return vec3(x, y, z);
}

void vec3::print() const
{
    std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}

vec3 operator*(double scalar, const vec3 &v)
{
    return vec3(scalar * v.x, scalar * v.y, scalar * v.z);
}
