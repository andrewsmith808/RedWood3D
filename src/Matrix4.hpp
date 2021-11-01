#ifndef __MATRIX4_HPP__
#define __MATRIX4_HPP__

#include "Vec.hpp"
#include <iostream>

class Matrix4 {
    private:
        double mat4[4][4];
    
    public:
        Matrix4();

        ~Matrix4();

        void identity();

        void zero();

        double getElement(int index1, int index2) const;

        void setElement(int index1, int index2, double value);

        Matrix4 scale(double sx, double sy, double sz);

        Matrix4 translate(double tx, double ty, double tz);

        Matrix4 rotateX(double angle);

        Matrix4 rotateY(double angle);

        Matrix4 rotateZ(double angle);

        Matrix4 perspective(double fov, double aspect, double znear, double zfar);

        Vec4 mulVec4(const Vec4& v);

        Matrix4 mulMatrix(Matrix4 m);

        Matrix4 lookAt(Vec3 eye, Vec3 target, Vec3 up);

        friend std::ostream& operator<<(std::ostream& out, const Matrix4& rhs);

};

#endif // __MATRIX_HPP__