#ifndef __VEC4_HPP__
#define __VEC4_HPP__

#include "Vec3.hpp"
#include "Vec2.hpp"

class Vec4 {
    private:
        double x, y, z, w;
    public:
        Vec4();
        Vec4(double x, double y, double z, double w);
        ~Vec4();
        Vec3 convertToVec3(const Vec4& v);
        Vec2 convertToVec2(const Vec4& v);
};

#endif // __VEC4_HPP__