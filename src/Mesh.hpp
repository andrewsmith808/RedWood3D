#ifndef __MESH_HPP__
#define __MESH_HPP__

#include "Vec.hpp"
#include "Display.hpp"
#include <vector>
#include <string>

static const int NUM_CUBE_VERTICIES = 8;
static const int NUM_CUBE_FACES = 12;

typedef struct {
    int a, b, c;
    color_t color;
} face_t;

class Mesh {
    private:
        Vec3* verticies;
        face_t* faces;

        Vec3 rotation;
        Vec3 scale;
        Vec3 translation;

        Vec3 cubeVerticies[NUM_CUBE_VERTICIES];
        face_t cubeFaces[NUM_CUBE_FACES];
    public:
        Mesh();
        Mesh(std::string filename);

        ~Mesh();

    private:
        void loadDefaultCubeData();
        void loadObjFileData();
};


#endif // __MESH_HPP__