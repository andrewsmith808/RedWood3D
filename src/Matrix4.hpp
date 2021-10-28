#ifndef __MATRIX4_HPP__
#define __MATRIX4_HPP__

#include "Vec.hpp"

class Matrix4 {
    private:
        double mat4[4][4];
    
    public:
        Matrix();

        ~Matrix();

        double getElement(int index1, int index2);

        double setElement(int index1, int index2);

        void identity();

        void scale(double sx, double sy, double sz);

        void translate(double tx, double ty, double tz);

        void rotateX(double angle);

        void rotateY(double angle);

        void rotateZ(double angle);

        void perspective(double fov, double aspect, double znear, double zfar);

        void mulVec4(const Vec4& v);

        void mulMatrix(Matrix4 m);

        void lookAt(Vec3 eye, Vec3 target, Vec3 up);

};

#endif // __MATRIX_HPP__