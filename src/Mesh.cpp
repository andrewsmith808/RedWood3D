#include "Mesh.hpp"

Mesh::Mesh() {
    this->verticies = nullptr;
    this->faces = nullptr;
    loadDefaultCubeData();
}

Mesh::Mesh(std::string filename) {
    this->verticies = nullptr;
    this->faces = nullptr;

    // TODO:: load in object file data
}

Mesh::~Mesh() {

}

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

    cubeVerticies[0] = vertex1;
    cubeVerticies[1] = vertex2;
    cubeVerticies[2] = vertex3;
    cubeVerticies[3] = vertex4;
    cubeVerticies[4] = vertex5;
    cubeVerticies[5] = vertex6;
    cubeVerticies[6] = vertex7;
    cubeVerticies[7] = vertex8;

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

    cubeFaces[0] = front1;
    cubeFaces[1] = front2;
    cubeFaces[2] = right1;
    cubeFaces[3] = right2;
    cubeFaces[4] = back1;
    cubeFaces[5] = back2;
    cubeFaces[6] = left1;
    cubeFaces[7] = left2;
    cubeFaces[8] = top1;
    cubeFaces[9] = top2;
    cubeFaces[10] = bottom1;
    cubeFaces[11] = bottom2;
}

void Mesh::loadObjFileData() {
    // TODO:: read obj file data format for other objects other than cube
}