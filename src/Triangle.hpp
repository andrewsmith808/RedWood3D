#ifndef __TRIANGLE_HPP__
#define __TRIANGLE_HPP__

#include "Display.hpp"
#include "Vec.hpp"

typedef struct {
    int a, b, c;
    color_t color;
} face_t;

class Triangle {
    private:
        Vec4 points[3];
        color_t color;

    public:
        Triangle();
        ~Triangle();

        void drawTrianglePixel(Display* display, color_t trianglePixelColor);

        void drawFilledTriangle(Display* display, color_t triangleColor);

    private:
        void intSwap(int* a, int* b);
        void doubleSwap(double* a, double* b);
        
};

#endif // __TRIANGLE_HPP__