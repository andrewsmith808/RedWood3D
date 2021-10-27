#include "vec.hpp"
#include <cmath>

// Implementations of Vec2 functions

Vec2::Vec2() {
    x = 0;
    y = 0;
}

Vec2::Vec2(double x, double y) {
    this->x = x;
    this->y = y;
}

Vec2::~Vec2() {
    delete this;
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