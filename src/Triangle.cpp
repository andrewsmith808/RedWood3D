#include "Triangle.hpp"
#include "Display.hpp"
#include <iostream>

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

void Triangle::drawFilledTriangle(Display* display) {
    sortVerticiesByHeight();

    //std::cout << "ordered points out of fn: " << points[0].getY() << " " << points[1].getY() << " " << points[2].getY() << std::endl;

    renderFlatBottom(display);

    //renderFlatTop(display);
}

Vec3 Triangle::barycentricWeights(Vec2 a, Vec2 b, Vec2 c, Vec2 p) {
    Vec2 ab = b.sub(a);
    Vec2 bc = c.sub(b);
    Vec2 ac = c.sub(a);
    Vec2 ap = p.sub(a);
    Vec2 bp = p.sub(b);

    //std::cout << "bary check 1" << std::endl;

    double areaABC = (ab.getX() * ac.getY() - ab.getY() * ac.getX());

    double alpha = (bc.getX() * bp.getY() - bp.getX() * bc.getY() / areaABC);

    double beta = (ap.getX() * ac.getY() - ac.getX() * ap.getY() / areaABC);

    double gamma = 1 - alpha - beta;

    //std::cout << "bary check 2" << std::endl;

    Vec3 result(alpha, beta, gamma);
    //std::cout << "initialized weights" << std::endl;
    return result;
}

void Triangle::drawTrianglePixel(int x, int y, Display* display, color_t trianglePixelColor) {
    Vec2 pixel(x, y);
    //std::cout << "Excuse me" << pixel.getX() << " " << pixel.getY() << std::endl;
    Vec2 pointA = Vec4_To_Vec2(points[0]);
    Vec2 pointB = Vec4_To_Vec2(points[1]);
    Vec2 pointC = Vec4_To_Vec2(points[2]);

    //std::cout << "call to barycentricWeights" << std::endl;
    Vec3 weights = barycentricWeights(pointA, pointB, pointC, pixel);
    //std::cout << "barycentricweights completed" << std::endl;

    double alpha = weights.getX();
    double beta = weights.getY();
    double gamma = weights.getZ();

    //std::cout << "weights applied" << std::endl;

    double interpolatedReciprocalW = (1 / points[0].getW()) * alpha + (1 / points[1].getW()) * beta + (1 / points[2].getW()) * gamma;

    interpolatedReciprocalW = 1.0 - interpolatedReciprocalW;

    if (interpolatedReciprocalW < display->getZBufferAt((display->getWindowWidth() * y) + x)) {
        //std::cout << "call to display->drawPixel from drawTrianglePixel" << std::endl;
        //display->drawPixel(x, y, trianglePixelColor);
        //display->setZbufferAt((display->getWindowWidth() * y) + x, interpolatedReciprocalW);
    }
}

void Triangle::renderFlatBottom(Display* display) {
    double inverseSlope1 = 0.0;
    double inverseSlope2 = 0.0;

    // cast to int to specify pixel coordinates in color buffer
    int x0 = points[0].getX();
    int y0 = points[0].getY();
    int x1 = points[1].getX();
    int y1 = points[1].getY();
    int x2 = points[2].getX();
    int y2 = points[2].getY();

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
                //std::cout << "call to DrawPixel from RenderFlatB" << std::endl;
                drawTrianglePixel(x, y, display, this->color);
            }
        }
    }
}

void Triangle::renderFlatTop(Display* display) {
    // double inverseSlope1 = 0.0;
    // double inverseSlope2 = 0.0;

    // // cast to int to specify pixel coordinates in color buffer
    // int x0 = static_cast<int>(points[0].getX());
    // int y0 = static_cast<int>(points[0].getY());
    // int x1 = static_cast<int>(points[1].getX());
    // int y1 = static_cast<int>(points[1].getY());
    // int x2 = static_cast<int>(points[2].getX());
    // int y2 = static_cast<int>(points[2].getY());

    // if (y2 - y1 != 0) 
    //     inverseSlope1 = (double)(x2 - x1) / abs(y2 - y1);
    // if (y2 - y0 != 0) 
    //     inverseSlope2 = (double)(x2 - x0) / abs(y2 - y0);

    // if (y2 - y1 != 0) {
    //     for (int y = y1; y <= y2; y++) {
    //         int xStart = x1 + (y - y1) * inverseSlope1;
    //         int xEnd = x0 + (y - y0) * inverseSlope2;

    //         if (xEnd < xStart) {
    //             intSwap(&xStart, &xEnd); // swap if x_start is to the right of x_end
    //         }

    //         for (int x = xStart; x < xEnd; x++) {
    //             std::cout << "call to DrawPixel from RenderFlatT" << std::endl;
    //             drawTrianglePixel(x, y, display, this->color);
    //         }
    //     }
    // }
}


void Triangle::sortVerticiesByHeight() {
    Vec4 temp;

    //std::cout << "unordered points: " << points[0].getY() << " " << points[1].getY() << " " << points[2].getY() << std::endl;

    if (points[0].getY() > points[1].getY()) {
        temp = points[1];
        points[1] = points[0];
        points[0] = temp;
    }
    if (points[1].getY() > points[2].getY()) {
        temp = points[2];
        points[2] = points[1];
        points[1] = temp;
    }
    if (points[0].getY() > points[1].getY()) {
        temp = points[1];
        points[1] = points[0];
        points[0] = temp;
    }

    //std::cout << "ordered points in fn: " << points[0].getY() << " " << points[1].getY() << " " << points[2].getY() << std::endl;
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

