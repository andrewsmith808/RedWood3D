#include "Mesh.hpp"

Mesh::Mesh() {
    loadDefaultCubeData();
}

Mesh::Mesh(std::string filename) {
    // TODO:: load in object file data
}

Mesh::~Mesh() {

}

double Mesh::getRotationX() const {return rotation.getX();}
double Mesh::getRotationY() const {return rotation.getY();}
double Mesh::getRotationZ() const {return rotation.getZ();}

double Mesh::getTranslationX() const {return translation.getX();}
double Mesh::getTranslationY() const {return translation.getY();}
double Mesh::getTranslationZ() const {return translation.getZ();}

double Mesh::getScaleX() const {return scale.getX();}
double Mesh::getScaleY() const {return scale.getY();}
double Mesh::getScaleZ() const {return scale.getZ();}

void Mesh::setRoationAll(double rx, double ry, double rz) {rotation.setX(rx); rotation.setY(ry); rotation.setZ(rz);}
void Mesh::setRotationX(double rx) {rotation.setX(rx);}
void Mesh::setRotationY(double ry) {rotation.setY(ry);}
void Mesh::setRotationZ(double rz) {rotation.setZ(rz);}

void Mesh::setTranslationAll(double tx, double ty, double tz) {translation.setX(tx);translation.setY(ty);translation.setZ(tz);}
void Mesh::setTranslationX(double tx) {translation.setX(tx);}
void Mesh::setTranslationY(double ty) {translation.setY(ty);}
void Mesh::setTranslationZ(double tz) {translation.setZ(tz);}

void Mesh::setScaleAll(double sx, double sy, double sz) {scale.setX(sx);scale.setY(sy);scale.setZ(sz);}
void Mesh::setScaleX(double sx){scale.setX(sx);}
void Mesh::setScaleY(double sy) {scale.setY(sy);}
void Mesh::setScaleZ(double sz) {scale.setZ(sz);}

void Mesh::loadDefaultCubeData() {
    color_t cubeColor = {0xFFFFFF88};

    Vec3 vertex1(-1, -1, -1);
    Vec3 vertex2(-1,  1, -1);
    Vec3 vertex3( 1,  1, -1);
    Vec3 vertex4( 1, -1, -1);
    Vec3 vertex5( 1,  1,  1);
    Vec3 vertex6( 1, -1,  1);
    Vec3 vertex7(-1,  1,  1);
    Vec3 vertex8(-1, -1,  1);

    verticies.push_back(vertex1);
    verticies.push_back(vertex2);
    verticies.push_back(vertex3);
    verticies.push_back(vertex4);
    verticies.push_back(vertex5);
    verticies.push_back(vertex6);
    verticies.push_back(vertex7);
    verticies.push_back(vertex8);

    face_t front1 = { .a = 1, .b = 2, .c = 3, .color = cubeColor };
    face_t front2 = { .a = 1, .b = 3, .c = 4, .color = cubeColor };

    face_t right1 = { .a = 4, .b = 3, .c = 5, .color = cubeColor };
    face_t right2 = { .a = 4, .b = 5, .c = 6, .color = cubeColor };
    
    face_t back1 = { .a = 6, .b = 5, .c = 7, .color = cubeColor };
    face_t back2 = { .a = 6, .b = 7, .c = 8, .color = cubeColor };

    face_t left1 = { .a = 8, .b = 7, .c = 2, .color = cubeColor };
    face_t left2 = { .a = 8, .b = 2, .c = 1, .color = cubeColor };
    
    face_t top1 = { .a = 2, .b = 7, .c = 5, .color = cubeColor };
    face_t top2 = { .a = 2, .b = 5, .c = 3, .color = cubeColor };

    face_t bottom1 = { .a = 6, .b = 8, .c = 1, .color = cubeColor };
    face_t bottom2 = { .a = 6, .b = 1, .c = 4, .color = cubeColor };

    faces.push_back(front1);
    faces.push_back(front2);
    faces.push_back(right1);
    faces.push_back(right2);
    faces.push_back(back1);
    faces.push_back(back2);
    faces.push_back(left1);
    faces.push_back(left2);
    faces.push_back(top1);
    faces.push_back(top2);
    faces.push_back(bottom1);
    faces.push_back(bottom2);
}

void Mesh::loadObjFileData() {
    // TODO:: read obj file data format for other objects other than cube
}