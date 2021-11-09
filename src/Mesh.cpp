#include "Mesh.hpp"

Mesh::Mesh() {
    rotation.x = 0;
    rotation.y = 0;
    rotation.z = 0;

    scale.x = 1.0;
    scale.y = 1.0;
    scale.z = 1.0;

    translation.x = 0;
    translation.y = 0;
    translation.z = 0;
   
    loadDefaultCubeData();
}

Mesh::~Mesh() {}

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