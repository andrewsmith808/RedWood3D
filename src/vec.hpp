#ifndef __VEC_HPP__
#define __VEC_HPP__

class Vec2 {
    private:
        double x, y;
    public:
        Vec2();
        Vec2(double x, double y);
        ~Vec2();
        double length();
        void add(const Vec2& v);
        void sub(const Vec2& v);
        void mul(double factor);
        void div(double factor);
        double dot(const Vec2& v);
        void normalize();
};

// class Vec3 {
//     private:
//         double x, y, z;
//     public:
//         double length();
//         void add(const Vec3& v);
//         void sub(const Vec3& v);
//         void mul(const Vec3& v);
//         void div(const Vec3& v);
//         void normalize(const Vec3& v);
//         Vec4 convertToVec4(const Vec3& v);
// };

// class Vec4 {
//     private:
//         double x, y, z, w;
//     public:
//         Vec3 convertToVec3(const Vec4& v);
//         Vec2 convertToVec2(const Vec4& v);
// };

#endif // __VEC_HPP__