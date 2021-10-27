#ifndef __VEC3_HPP__
#define __VEC3_HPP__

class Vec3 {
    private:
        double x, y, z;
    public:
        Vec3();
        Vec3(double x, double y, double z);
        ~Vec3();

        double getX() const;
        double getY() const;
        double getZ() const;

        double length();
        void add(const Vec3& v);
        void sub(const Vec3& v);
        void div(double factor);
        void normalize();
        void mul(double factor);
        double dot(const Vec3& v);
        Vec3 cross(const Vec3& v);
        Vec3 rotateX(double angle);
        Vec3 rotateY(double angle);
        Vec3 rotateZ(double angle);
};

#endif // __VEC3_HPP__