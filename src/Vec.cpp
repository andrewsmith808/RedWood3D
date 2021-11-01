#include "Vec.hpp"
#include <cmath>

// Implementations of Vec2 functions

Vec2::Vec2() :
    x(0), y(0) {}

Vec2::Vec2(double x, double y) :
    x(x), y(y) {}

Vec2::~Vec2() {
    delete this;
}

double Vec2::getX() const {
    return x;
}

double Vec2::getY() const {
    return y;
}

double Vec2::length() {
    return sqrt(x * x + y * y);
}

void Vec2::add(const Vec2& v) {
    x = x + v.x;
    y = y + v.y;
}
void Vec2::sub(const Vec2& v) {
    x = x - v.x;
    y = y - v.y;
}
void Vec2::mul(double factor) {
    x = x * factor;
    y = y * factor;
}
void Vec2::div(double factor) {
    x = x / factor;
    y = y / factor;
}

double Vec2::dot(const Vec2& v) {
    return x * v.x + y * v.y;
}

void Vec2::normalize() {
    double length = this->length();
    x = x / length;
    y = y / length;
}

// Implementation of Vec3 functions
Vec3::Vec3() :
    x(0), y(0), z(0) {}

Vec3::Vec3(double x, double y, double z) :
    x(x), y(y), z(z) {}

Vec3::~Vec3() {
    // no dynamic memory allocated, default behavior
}

double Vec3::getX() const {
    return x;
}

double Vec3::getY() const {
    return y;
}

double Vec3::getZ() const {
    return z;
}

double Vec3::length() {
    return sqrt(x * x + y * y + z * z);
}

void Vec3::add(const Vec3& v) {
    x = x + v.x;
    y = y + v.y;
    z = z + v.z;
}
Vec3 Vec3::sub(const Vec3& v) {
    double X = x - v.x;
    double Y = y - v.y;
    double Z = z - v.z;

    Vec3 result(X, Y, Z);
    return result;
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

double Vec3::dot(const Vec3& v) {
    return x * v.x + y * v.y + z * v.z;
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
        -this->x * sin(angle) + this->z * cos(angle)
    );
    return rotatedVector;
}
Vec3 Vec3::rotateZ(double angle) {
    Vec3 rotatedVector(
        this->x * cos(angle) - this->y * sin(angle),
        this->x * sin(angle) + this->y * cos(angle),
        this->z
    );
    return rotatedVector;
}

// Implemntation of Vec4 functions
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

void Vec4::setX(double value) {
    x = value;
}
void Vec4::setY(double value) {
    y = value;
}
void Vec4::setZ(double value) {
    z = value;
}
void Vec4::setW(double value) {
    w = value;
}