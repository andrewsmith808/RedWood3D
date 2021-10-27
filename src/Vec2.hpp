#ifndef __VEC2_HPP__
#define __VEC2_HPP__

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

#endif // __VEC2_HPP__