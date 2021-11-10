#include "Triangle.hpp"
#include "Display.hpp"
#include <iostream>

Triangle::Triangle() {
    Vec2 vec1;
    Vec2 vec2;
    Vec2 vec3;

    points[0] = vec1;
    points[1] = vec2;
    points[2] = vec3;

    color.color = 0xFF994588;

    avgDepth = 0;
}

Triangle::~Triangle() {}

// Draw a triangle using three lines
void Triangle::drawTriangle(Display* display) {
    int x0 = points[0].x;
    int y0 = points[0].y;
    int x1 = points[1].x;
    int y1 = points[1].y;
    int x2 = points[2].x;
    int y2 = points[2].y;

    //std::cout << x0 << " " << y0 << " "<< x1 << " "<< y1 << " "<< x2 << " "<< y2 << std::endl;

    display->drawLine(x0, y0, x1, y1, this->color);
    display->drawLine(x1, y1, x2, y2, this->color);
    display->drawLine(x2, y2, x0, y0, this->color);
}

///////////////////////////////////////////////////////////////////////////////
// Draw a filled triangle with the flat-top/flat-bottom method
// We split the original triangle in two, half flat-bottom and half flat-top
///////////////////////////////////////////////////////////////////////////////
//
//          (x0,y0)
//            / \
//           /   \
//          /     \
//         /       \
//        /         \
//   (x1,y1)------(Mx,My)
//       \_           \
//          \_         \
//             \_       \
//                \_     \
//                   \    \
//                     \_  \
//                        \_\
//                           \
//                         (x2,y2)
//
///////////////////////////////////////////////////////////////////////////////
void Triangle::drawFilledTriangle(Display* display) {
    sortVerticiesByHeight();

    int x0 = points[0].x;
    int y0 = points[0].y;
    int x1 = points[1].x;
    int y1 = points[1].y;
    int x2 = points[2].x;
    int y2 = points[2].y;

    if (y1 == y2) {
        renderFlatBottom(x0, y0, x1, y1, x2, y2, display, this->color);
    } else if (y0 == y1) {
        renderFlatTop(x0, y0, x1, y1, x2, y2, display, this->color);
    } else {
        int My = y1;
        int Mx = (((x2 - x0) *(y1 - y0)) / (y2 - y0)) + x0;

        renderFlatBottom(x0, y0, x1, y1, Mx, My, display, this->color);

        renderFlatTop(x1, y1, Mx, My, x2, y2, display, this->color);
    }
}

///////////////////////////////////////////////////////////////////////////////
// Draw a filled a triangle with a flat bottom
///////////////////////////////////////////////////////////////////////////////
//
//        (x0,y0)
//          / \
//         /   \
//        /     \
//       /       \
//      /         \
//  (x1,y1)------(x2,y2)
//
///////////////////////////////////////////////////////////////////////////////
void Triangle::renderFlatBottom(int x0, int y0, int x1, int y1, int x2, int y2, Display* display, color_t color) {
    /// Find the two slopes (two triangle legs)
    float inverseSlope1 = (double)(x1 - x0) / (y1 - y0);
    float inverseSlope2 = (double)(x2 - x0) / (y2 - y0);

    // Start x_start and x_end from the top vertex (x0,y0)
    float xStart = x0;
    float xEnd = x0;

    // Loop all the scanlines from top to bottom
    for (int y = y0; y <= y2; y++) {
        display->drawLine(xStart, y, xEnd, y, color);
        xStart += inverseSlope1;
        xEnd += inverseSlope2;
    }
}

///////////////////////////////////////////////////////////////////////////////
// Draw a filled a triangle with a flat top
///////////////////////////////////////////////////////////////////////////////
//
//  (x0,y0)------(x1,y1)
//      \         /
//       \       /
//        \     /
//         \   /
//          \ /
//        (x2,y2)
//
///////////////////////////////////////////////////////////////////////////////
void Triangle::renderFlatTop(int x0, int y0, int x1, int y1, int x2, int y2, Display* display, color_t color) {
    // Find the two slopes (two triangle legs)
    float inverseSlope1 = (double)(x2 - x0) / (y2 - y0);
    float inverseSlope2 = (double)(x2 - x1) / (y2 - y1);

    // Start x_start and x_end from the bottom vertex (x2,y2)
    float xStart = x2;
    float xEnd = x2;

    // Loop all the scanlines from bottom to top
    for (int y = y2; y >= y0; y--) {
        display->drawLine(xStart, y, xEnd, y, color);
        xStart -= inverseSlope1;
        xEnd -= inverseSlope2;
    }
}


void Triangle::sortVerticiesByHeight() {
    Vec2 temp;

    //std::cout << "unordered points: " << points[0].y << " " << points[1].y << " " << points[2].y << std::endl;

    if (points[0].y > points[1].y) {
        temp = points[1];
        points[1] = points[0];
        points[0] = temp;
    }
    if (points[1].y > points[2].y) {
        temp = points[2];
        points[2] = points[1];
        points[1] = temp;
    }
    if (points[0].y > points[1].y) {
        temp = points[1];
        points[1] = points[0];
        points[0] = temp;
    }

    //std::cout << "ordered points: " << points[0].y << " " << points[1].y << " " << points[2].y << std::endl;
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

