#include "Vec4.hpp"

Vec4::Vec4() :
    x(0), y(0), z(0), w(1) {}

Vec4::Vec4(double x, double y, double z, double w) :
    x(x), y(y), z(z), w(w) {}

Vec4::~Vec4() {
    // no dynamically allocated memory default behavior
}

Vec3 Vec4_To_Vec3(const Vec4& v) {
    Vec3 result(v.getX(), v.getY(), v.getZ());
    return result;
}

Vec2 Vec4_To_Vec2(const Vec4& v) {
    Vec2 result(v.getX(), v.getY());
    return result;
}

Vec4 Vec3_To_Vec4(const Vec3& v) {
    Vec4 result(v.getX(), v.getY(), v.getZ(), 1.0);
    return result;
}

double Vec4::getX() const {
    return x;
}

double Vec4::getY() const {
    return y;
}

double Vec4::getZ() const {
    return z;
}

double Vec4::getW() const {
    return w;
}