#include "Triangle.hpp"
#include "Display.hpp"

Triangle::Triangle() {
    Vec4 vec1;
    Vec4 vec2;
    Vec4 vec3;

    points[0] = vec1;
    points[1] = vec2;
    points[2] = vec3;

    color.color = 0xFF994588;
}

Triangle::~Triangle() {
    // no new memory allocated
}

void Triangle::drawTrianglePixel(Display* display, color_t ttrianglePixelColor) {
    // TODO:: Implement DEPTH INTERPOLATION drawing of pixel for triangle
}

void Triangle::drawFilledTriangle(Display* display, color_t triangleColor) {
    // TODO:: Implement FLAT AND TOP TRIANGLE FILLING
}

void Triangle::intSwap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void Triangle::doubleSwap(double* a, double* b) {
    double tmp = *a;
    *a = *b;
    *b = tmp;
}

