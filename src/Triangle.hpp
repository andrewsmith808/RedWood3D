#ifndef __TRIANGLE_HPP__
#define __TRIANGLE_HPP__

#include "Display.hpp"
#include "Vec.hpp"

class Triangle {
    public:
        Vec4 points[3];
        color_t color;

    public:
        Triangle();
        ~Triangle();

        void drawFilledTriangle(Display* display);

    private:
        void intSwap(int* a, int* b);

        void doubleSwap(double* a, double* b);

        void sortVerticiesByHeight();

        void renderFlatBottom(Display* display);

        void renderFlatTop(Display* display);

        void drawTrianglePixel(int x, int y, Display* display, color_t trianglePixelColor);

        Vec3 barycentricWeights(Vec2 a, Vec2 b, Vec2 c, Vec2 p);
        
};

#endif // __TRIANGLE_HPP__