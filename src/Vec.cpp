#include "Vec.hpp"
#include <cmath>
#include <iomanip>

//=====================================================
// Implementations of Vec2 functions
//=====================================================
Vec2::Vec2() :
    x(0), y(0) {}

Vec2::Vec2(double x, double y) :
    x(x), y(y) {}

Vec2::~Vec2() {}

double Vec2::length() {
    return sqrt((x * x) + (y * y));
}

Vec2 Vec2::add(const Vec2& v) {
    double a = x + v.x;
    double b = y + v.y;

    Vec2 result(a, b);
    return result;
}
Vec2 Vec2::sub(const Vec2& v) {
    double a = x - v.x;
    double b = y - v.y;

    Vec2 result(a, b);
    return result;
}
Vec2 Vec2::mul(double factor) {
    double a = x * factor;
    double b = y * factor;

    Vec2 result(a, b);
    return result;
}

Vec2 Vec2::div(double factor) {
    double a = x / factor;
    double b = y / factor;

    Vec2 result(a, b);
    return result;
}

double Vec2::dot(const Vec2& v) {
    return (x * v.x) + (y * v.y);
}

void Vec2::normalize() {
    double length = this->length();
    x = x / length;
    y = y / length;
}

std::ostream& operator<<(std::ostream& out, const Vec2& rhs) {
    std::cout << "Vec2: " << "(.x = " << rhs.x << ", .y = " << rhs.y << ")";
    return out;
}


//=====================================================
// Implementations of Vec3 functions
//=====================================================
Vec3::Vec3() :
    x(0), y(0), z(0) {}

Vec3::Vec3(double x, double y, double z) :
    x(x), y(y), z(z) {}

Vec3::~Vec3() {}

double Vec3::length() {
    return sqrt(x*x + y*y + z*z);
}

Vec3 Vec3::add(const Vec3& v) {
    double a = x + v.x;
    double b = y + v.y;
    double c = z + v.z;

    Vec3 result(a, b, c);
    return result;
}

Vec3 Vec3::sub(const Vec3& v) {
    double a = x - v.x;
    double b = y - v.y;
    double c = z - v.z;

    Vec3 result(a, b, c);
    return result;
}

Vec3 Vec3::mul(double factor) {
    double a = x * factor;
    double b = y * factor;
    double c = z * factor;

    Vec3 result(a, b, c);
    return result;
}

Vec3 Vec3::div(double factor) {
    double a = x / factor;
    double b = y / factor;
    double c = z / factor;

    Vec3 result(a, b, c);
    return result;
}

void Vec3::normalize() {
    double length = this->length();
    x /= length;
    y /= length;
    z /= length;
}

double Vec3::dot(const Vec3& v) {
    return (x * v.x) + (y * v.y) + (z * v.z);
}

Vec3 Vec3::cross(const Vec3& v) {
    double a = y * v.z - z * v.y;
    double b = z * v.x - x * v.z;
    double c = x * v.y - y * v.x;

    Vec3 result(a, b, c);
    return result;
}
Vec3 Vec3::rotateX(double angle) {
    double a = x;
    double b = y * cos(angle) - z * sin(angle);
    double c = z * sin(angle) + z * cos(angle);
    
    Vec3 result(a, b, c);
    return result;
}
Vec3 Vec3::rotateY(double angle) {
    double a = x * cos(angle) + z * sin(angle);
    double b = y;
    double c = -x * sin(angle) + z * cos(angle);

    Vec3 result(a, b, c);
    return result;
}
Vec3 Vec3::rotateZ(double angle) {
    double a = x * cos(angle) - y * sin(angle);
    double b = x * sin(angle) + y * cos(angle);
    double c = z;

    Vec3 result(a, b, c);
    return result;
}

std::ostream& operator<<(std::ostream& out, const Vec3& rhs) {
    std::cout << "Vec3: " << "(.x = " << rhs.x << ", .y = " << rhs.y << ", .z = " << rhs.z << ")";
    return out;
}

//=====================================================
// Implementations of Vec3 functions
//=====================================================
Vec4::Vec4() :
    x(0), y(0), z(0), w(1) {}

Vec4::Vec4(double x, double y, double z, double w) :
    x(x), y(y), z(z), w(w) {}

Vec4::~Vec4() {}

std::ostream& operator<<(std::ostream& out, const Vec4& rhs) {
    std::cout << std::setprecision(6) << std::fixed << "Vec4: " << "(.x = " << rhs.x << ", .y = " << rhs.y << ", .z = " << rhs.z << ", .w = " << rhs.w << ")";
    return out;
}

Vec3 Vec4_To_Vec3(const Vec4& v) {
    Vec3 result(v.x, v.y, v.z);
    return result;
}

Vec2 Vec4_To_Vec2(const Vec4& v) {
    Vec2 result(v.x, v.y);
    return result;
}

Vec4 Vec3_To_Vec4(const Vec3& v) {
    Vec4 result(v.x, v.y, v.z, 1.0);
    return result;
}