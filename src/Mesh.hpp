#ifndef __MESH_HPP__
#define __MESH_HPP__

#include "Vec.hpp"
#include "Display.hpp"
#include <vector>
#include <string>

typedef struct {
    int a, b, c;
    color_t color;
} face_t;

class Mesh {
    public:
        Vec3 rotation;
        Vec3 scale;
        Vec3 translation;
        std::vector<Vec3> verticies;
        std::vector<face_t> faces;
        
        Mesh();
        ~Mesh();

    private:
        void loadDefaultCubeData();
};

#endif // __MESH_HPP__