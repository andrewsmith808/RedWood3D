#include "Vec3.hpp"
#include <cmath>

Vec3::Vec3() :
    x(0), y(0), z(0) {}

Vec3::Vec3(double x, double y, double z) :
    x(x), y(y), z(z) {}

Vec3::~Vec3() {
    delete this;
}

double Vec3::length() {
    return sqrt(x * x + y * y + z * z);
}

void Vec3::add(const Vec3& v) {
    x = x + v.x;
    y = y + v.y;
    z = z + v.z;
}
void Vec3::sub(const Vec3& v) {
    x = x - v.x;
    y = y - v.y;
    z = z - v.z;
}

void Vec3::mul(double factor) {
    x *= factor;
    y *= factor;
    z *= factor;
}

void Vec3::div(double factor) {
    x /= factor;
    y /= factor;
    z /= factor;
}
void Vec3::normalize() {
    double length = this->length();
    x /= length;
    y /= length;
    z /= length;
}

Vec3 Vec3::cross(const Vec3& v) {
    Vec3 result (
        this->y * v.z - this->z * v.y,
        this->z * v.x - this->x * v.z,
        this->x * v.y - this->y * v.x
    );
    return result;
}
Vec3 Vec3::rotateX(double angle) {
    Vec3 rotatedVector (
        this->x,
        this->y * cos(angle) - this->z * sin(angle),
        this->y * sin(angle) + this->z * cos(angle)
    );
    return rotatedVector;
}
Vec3 Vec3::rotateY(double angle) {
    Vec3 rotatedVector(
        this->x * cos(angle) + this->z * sin(angle),
        this->y,
        this->-x * sin(angle) + this->z * cos(angle)
    );
    return rotatedVector;
}
Vec3 Vec3::rotateZ(double angle) {
    vec3_t rotatedVector(
        this->x * cos(angle) - this->y * sin(angle),
        this->x * sin(angle) + this->y * cos(angle),
        this->z
    );
    return rotatedVector;
}