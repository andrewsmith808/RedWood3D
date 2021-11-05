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



        double getRotationX() const;
        double getRotationY() const;
        double getRotationZ() const;

        double getTranslationX() const;
        double getTranslationY() const;
        double getTranslationZ() const;

        double getScaleX() const;
        double getScaleY() const;
        double getScaleZ() const;


        void setRoationAll(double rx, double ry, double rz);
        void setRotationX(double rx);
        void setRotationY(double ry);
        void setRotationZ(double rz);

        void setTranslationAll(double tx, double ty, double tz);
        void setTranslationX(double tx);
        void setTranslationY(double ty);
        void setTranslationZ(double tz);

        void setScaleAll(double sx, double sy, double sz);
        void setScaleX(double sx);
        void setScaleY(double sy);
        void setScaleZ(double sz);


    private:
        void loadDefaultCubeData();
        void loadObjFileData();
};


#endif // __MESH_HPP__