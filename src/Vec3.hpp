#ifndef __VEC3_HPP__
#define __VEC3_HPP__

#include "Vec4.hpp"

class Vec3 {
    private:
        double x, y, z;
    public:
        Vec3();
        Vec3(double x, double y, double z);
        ~Vec3();
        double length();
        void add(const Vec3& v);
        void sub(const Vec3& v);
        void mul(const Vec3& v);
        void div(const Vec3& v);
        void normalize(const Vec3& v);
        Vec4 convertToVec4(const Vec3& v);
};

#endif // __VEC3_HPP__