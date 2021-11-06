#ifndef __TRIANGLE_HPP__
#define __TRIANGLE_HPP__

#include "Display.hpp"
#include "Vec.hpp"

class Triangle {
    public:
        Vec4 points[3];
        color_t color;

        Triangle();
        ~Triangle();

        void drawTriangle(Display* display);

        void drawFilledTriangle(Display* display);

    private:
        void intSwap(int* a, int* b);

        void doubleSwap(double* a, double* b);

        void sortVerticiesByHeight();

        void renderFlatTop(int x0, int y0, int x1, int y1, int x2, int y2, Display* display, color_t color);

        void renderFlatBottom(int x0, int y0, int x1, int y1, int x2, int y2, Display* display, color_t color);
};

#endif // __TRIANGLE_HPP__