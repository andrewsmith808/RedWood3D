#ifndef __VEC_HPP__
#define __VEC_HPP__

class Vec2 {
    private:
        double x, y;
    public:
        Vec2();
        Vec2(double x, double y);
        ~Vec2();

        double getX() const;
        double getY() const;

        double length();
        void add(const Vec2& v);
        Vec2 sub(const Vec2& v);
        void mul(double factor);
        void div(double factor);
        double dot(const Vec2& v);
        void normalize();
};

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

        void setX(double value);
        void setY(double value);
        void setZ(double value);

        double length();
        Vec3 add(const Vec3& v);
        Vec3 sub(const Vec3& v);
        void div(double factor);
        void normalize();
        void mul(double factor);
        double dot(const Vec3& v);
        Vec3 cross(const Vec3& v);
        Vec3 rotateX(double angle);
        Vec3 rotateY(double angle);
        Vec3 rotateZ(double angle);
};

class Vec4 {
    private:
        double x, y, z, w;
    public:
        Vec4();
        Vec4(double x, double y, double z, double w);
        ~Vec4();

        double getX() const;
        double getY() const;
        double getZ() const;
        double getW() const;

        void setX(double value);
        void setY(double value);
        void setZ(double value);
        void setW(double value);
};

// global conversion functions
Vec3 Vec4_To_Vec3(const Vec4& v);
Vec2 Vec4_To_Vec2(const Vec4& v);
Vec4 Vec3_To_Vec4(const Vec3& v);


#endif // __VEC_HPP__