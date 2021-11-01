#include "Matrix4.hpp"
#include <cmath>

Matrix4::Matrix4() {
    this->identity();
}

Matrix4::~Matrix4() {
    // no memory allocated
}

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

double Matrix4::getElement(int index1, int index2) const {
    return mat4[index1][index2];
}

void Matrix4::setElement(int index1, int index2, double value) {
    mat4[index1][index2] = value;
}

Matrix4 Matrix4::scale(double sx, double sy, double sz) {
    Matrix4 scale;
    scale.setElement(0, 0, sx);
    scale.setElement(1, 1, sy);
    scale.setElement(2, 2, sz);
    return scale;
}

Matrix4 Matrix4::translate(double tx, double ty, double tz) {
    Matrix4 trans;
    trans.setElement(0, 3, tx);
    trans.setElement(1, 3, ty);
    trans.setElement(2, 3, tz);
    return trans;
}

Matrix4 Matrix4::rotateX(double angle) {
    double c = cos(angle);
    double s = sin(angle);

    Matrix4 m;
    m.setElement(1, 1, c);
    m.setElement(1, 2, -s);
    m.setElement(2, 1, s);
    m.setElement(2, 2, c);
    return m;
}

Matrix4 Matrix4::rotateY(double angle) {
    double c = cos(angle);
    double s = sin(angle);

    Matrix4 m;
    m.setElement(0, 0, c);
    m.setElement(0, 2, -s);
    m.setElement(2, 0, s);
    m.setElement(2, 2, c);
    return m;
}

Matrix4 Matrix4::rotateZ(double angle) {
    double c = cos(angle);
    double s = sin(angle);

    Matrix4 m;
    m.setElement(0, 0, c);
    m.setElement(0, 1, -s);
    m.setElement(1, 0, s);
    m.setElement(1, 1, c);
    return m;
}

Matrix4 Matrix4::perspective(double fov, double aspect, double znear, double zfar) {
    Matrix4 m;
    m.zero();
    m.setElement(0, 0, aspect * (1 / tan(fov / 2)));
    m.setElement(1, 1, 1 / tan(fov / 2));
    m.setElement(2, 2, zfar / (zfar - znear));
    m.setElement(2, 3, (-zfar * znear) / (zfar - znear));
    m.setElement(3, 2, 1.0);
    return m;
}


Vec4 Matrix4::mulVec4(const Vec4& v) {
    double x = getElement(0, 0) * v.getX() + getElement(0, 1) * v.getY() + getElement(0, 2) * v.getZ() + getElement(0, 3) * v.getW();
    double y = getElement(1, 0) * v.getX() + getElement(1, 1) * v.getY() + getElement(1, 2) * v.getZ() + getElement(1, 3) * v.getW();
    double z = getElement(2, 0) * v.getX() + getElement(2, 1) * v.getY() + getElement(2, 2) * v.getZ() + getElement(2, 3) * v.getW();
    double w = getElement(3, 0) * v.getX() + getElement(3, 1) * v.getY() + getElement(3, 2) * v.getZ() + getElement(3, 3) * v.getW();

    Vec4 result(x, y, z, w);
    return result;
}



Matrix4 Matrix4::mulMatrix(Matrix4 m) {
    Matrix4 result;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            double product = getElement(i, 0) * m.getElement(0, j)
                            + getElement(i, 1) * m.getElement(1, j)
                            + getElement(i, 2) * m.getElement(2, j)
                            + getElement(i, 3) * m.getElement(3, j);

            result.setElement(i, j, product);
        }
    }
    return result;
}

Matrix4 Matrix4::lookAt(Vec3 eye, Vec3 target, Vec3 up) {
    Vec3 z = target.sub(eye);
    z.normalize();
    Vec3 x = up.cross(z);
    x.normalize();
    Vec3 y = z.cross(x);

    Matrix4 viewMatrix;
    viewMatrix.zero();

    viewMatrix.setElement(0, 0, x.getX());
    viewMatrix.setElement(0, 1, x.getY());
    viewMatrix.setElement(0, 2, x.getZ());
    viewMatrix.setElement(0, 3, -x.dot(eye));

    viewMatrix.setElement(1, 0, y.getX());
    viewMatrix.setElement(1, 1, y.getY());
    viewMatrix.setElement(1, 2, y.getZ());
    viewMatrix.setElement(1, 3, -y.dot(eye));

    viewMatrix.setElement(2, 0, z.getX());
    viewMatrix.setElement(2, 1, z.getY());
    viewMatrix.setElement(2, 2, z.getZ());
    viewMatrix.setElement(2, 3, -z.dot(eye));

    viewMatrix.setElement(3, 3, 1);

    return viewMatrix;
}


std::ostream& operator<<(std::ostream& out, const Matrix4& rhs) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            out << rhs.getElement(i, j) << " ";
        }
        out << std::endl;
    }
    return out;
}


