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
    return sqrt(x*x + y*y + z*z);
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

void div(double factor) {
    x /= facotr;
    y /= facotr;
    z /= factor;
}
void normalize() {
    double length = this->length();
    x /= length;
    y /= length;
    z /= length;
}