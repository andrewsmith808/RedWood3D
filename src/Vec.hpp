#ifndef __VEC_HPP__
#define __VEC_HPP__

#include <iostream>
class Vec2 {
    public:
        double x, y;

        Vec2();
        Vec2(double x, double y);
        ~Vec2();

        double length();
        Vec2 add(const Vec2& v);
        Vec2 sub(const Vec2& v);
        Vec2 mul(double factor);
        Vec2 div(double factor);
        double dot(const Vec2& v);
        void normalize();
        friend std::ostream& operator<<(std::ostream& out, const Vec2& rhs);
};

class Vec3 {
    public:
        double x, y, z;
        Vec3();
        Vec3(double x, double y, double z);
        ~Vec3();

        double length();
        Vec3 add(const Vec3& v);
        Vec3 sub(const Vec3& v);
        Vec3 mul(double factor);
        Vec3 div(double factor);
        Vec3 normalize();

        double dot(const Vec3& v);
        Vec3 cross(const Vec3& v);
        Vec3 rotateX(double angle);
        Vec3 rotateY(double angle);
        Vec3 rotateZ(double angle);

        friend std::ostream& operator<<(std::ostream& out, const Vec3& rhs);
};

class Vec4 {
    public:
        double x, y, z, w;
        Vec4();
        Vec4(double x, double y, double z, double w);
        ~Vec4();
        friend std::ostream& operator<<(std::ostream& out, const Vec4& rhs);
};

// global conversion functions
Vec3 Vec4_To_Vec3(const Vec4& v);
Vec2 Vec4_To_Vec2(const Vec4& v);
Vec4 Vec3_To_Vec4(const Vec3& v);


#endif // __VEC_HPP__