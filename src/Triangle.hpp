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

        void drawFilledTriangle(Display* display, color_t triangleColor);

    private:
        void intSwap(int* a, int* b);

        void doubleSwap(double* a, double* b);

        void sortVerticiesByHeight();

        void renderFlatBottom(Display* display, color_t triangleColor);

        void drawTrianglePixel(int x, int y, Display* display, color_t trianglePixelColor);
        
};

#endif // __TRIANGLE_HPP__