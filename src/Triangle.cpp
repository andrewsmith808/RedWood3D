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

void Triangle::drawTrianglePixel(Display* display, color_t trianglePixelColor) {
    // TODO:: Implement DEPTH INTERPOLATION drawing of pixel for triangle
    
}

void Triangle::drawFilledTriangle(Display* display, color_t triangleColor) {
    // TODO:: Implement FLAT AND TOP TRIANGLE FILLING
    sortVerticiesByHeight();

    renderFlatBottom(display, triangleColor);

}

void Triangle::renderFlatBottom(Display* display, color_t triangleColor) {
    double inverseSlope1 = 0.0;
    double inverseSlope2 = 0.0;

    // cast to int to specify pixel coordinates in color buffer
    int x0 = static_cast<int>(points[0].getX());
    int y0 = static_cast<int>(points[0].getY());
    int x1 = static_cast<int>(points[1].getX());
    int y1 = static_cast<int>(points[1].getY());
    int x2 = static_cast<int>(points[2].getX());
    int y2 = static_cast<int>(points[2].getY());

    if (y1 - y0 != 0) 
        inverseSlope1 = (double)(x1 - x0) / abs(y1 - y0);
    if (y2 - y0 != 0) 
        inverseSlope2 = (double)(x2 - x0) / abs(y2 - y0);

    if (y1 - y0 != 0) {
        for (int y = y0; y <= y1; y++) {
            int xStart = x1 + (y - y1) * inverseSlope1;
            int xEnd = x0 + (y - y0) * inverseSlope2;

            if (xEnd < xStart) {
                intSwap(&xStart, &xEnd);
            }

            for (int x = xStart; x < xEnd; x++) {
                drawTrianglePixel(display, triangleColor);
            }
        }
    }
}

void Triangle::sortVerticiesByHeight() {
    Vec4 temp;
    if (points[0].getY() > points[1].getY()) {
        temp = points[1];
        points[1] = points[0];
        points[0] = temp;
    }
    if (points[1].getY() > points[2].getY()) {
        temp = points[2];
        points[2] = points[1];
        points[2] = temp;
    }
    if (points[0].getY() > points[1].getY()) {
        temp = points[1];
        points[1] = points[0];
        points[0] = temp;
    }
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

