#include "Matrix4.hpp"
#include <cmath>

Matrix4::Matrix4() {
    this->identity();
}

Matrix4::~Matrix4() {}

void Matrix4::identity() {
    mat4[0][0] = 1;
    mat4[0][1] = 0;
    mat4[0][2] = 0;
    mat4[0][3] = 0;

    mat4[1][0] = 0;
    mat4[1][1] = 1;
    mat4[1][2] = 0;
    mat4[1][3] = 0;

    mat4[2][0] = 0;
    mat4[2][1] = 0;
    mat4[2][2] = 1;
    mat4[2][3] = 0;

    mat4[3][0] = 0;
    mat4[3][1] = 0;
    mat4[3][2] = 0;
    mat4[3][3] = 1;
}

void Matrix4::zero() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            mat4[i][j] = 0;
        }
    }
}

Matrix4 Matrix4::scale(double sx, double sy, double sz) {
    Matrix4 scale;
    scale.mat4[0][0] = sx;
    scale.mat4[1][1] = sy;
    scale.mat4[2][2] = sz;
    return scale;
}

Matrix4 Matrix4::translate(double tx, double ty, double tz) {
    Matrix4 trans;
    trans.mat4[0][3] = tx;
    trans.mat4[1][3] = ty;
    trans.mat4[2][3] = tz;
    return trans;
}

Matrix4 Matrix4::rotateX(double angle) {
    double c = cos(angle);
    double s = sin(angle);

    Matrix4 m;
    m.mat4[1][1] = c;
    m.mat4[1][2] = -s;
    m.mat4[2][1] = s;
    m.mat4[2][2] = c;
    return m;
}

Matrix4 Matrix4::rotateY(double angle) {
    double c = cos(angle);
    double s = sin(angle);

    Matrix4 m;
    m.mat4[0][0] = c;
    m.mat4[0][2] = s;
    m.mat4[2][0] = -s;
    m.mat4[2][2] = c;
    return m;
}

Matrix4 Matrix4::rotateZ(double angle) {
    double c = cos(angle);
    double s = sin(angle);

    Matrix4 m;
    m.mat4[0][0] = c;
    m.mat4[0][1] = -s;
    m.mat4[1][0] = s;
    m.mat4[1][1] = c;
    return m;
}

Vec4 Matrix4::mulVec4(const Vec4& v) {
    Vec4 result;
    result.x = mat4[0][0] * v.x + mat4[0][1] * v.y + mat4[0][2] * v.z + mat4[0][3] * v.w;
    result.y = mat4[1][0] * v.x + mat4[1][1] * v.y + mat4[1][2] * v.z + mat4[1][3] * v.w;
    result.z = mat4[2][0] * v.x + mat4[2][1] * v.y + mat4[2][2] * v.z + mat4[2][3] * v.w;
    result.w = mat4[3][0] * v.x + mat4[3][1] * v.y + mat4[3][2] * v.z + mat4[3][3] * v.w;
    return result;
}



Matrix4 Matrix4::mulMatrix(Matrix4 b) {
    Matrix4 result;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.mat4[i][j] = mat4[i][0] * b.mat4[0][j] + mat4[i][1] * b.mat4[1][j] + mat4[i][2] * b.mat4[2][j] + mat4[i][3] * b.mat4[3][j];
        }
    }
    return result;
}

Matrix4 Matrix4::perspective(double fov, double aspect, double znear, double zfar) {
    Matrix4 m;
    m.zero();
    m.mat4[0][0] = aspect * (1 / tan(fov / 2));
    m.mat4[1][1] = 1 / tan(fov / 2);
    m.mat4[2][2] = zfar / (zfar - znear);
    m.mat4[2][3] = (-zfar * znear) / (zfar - znear);
    m.mat4[3][2] = 1.0;
    return m;
}

Vec4 Matrix4::mulProjection(Vec4 v) {
    Vec4 result = this->mulVec4(v);

    if (result.w != 0.0) {
        result.x /= result.w;
        result.y /= result.w;
        result.z /= result.w;
    }
    return result;
}

std::ostream& operator<<(std::ostream& out, const Matrix4& rhs) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            out << rhs.mat4[i][j] << " ";
        }
        out << std::endl;
    }
    return out;
}


