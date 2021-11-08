#ifndef __RED_WOOD_ENGINE_HPP__
#define __RED_WOOD_ENGINE_HPP__

#include "Display.hpp"
#include "Vec.hpp"
#include "Triangle.hpp"
#include "Matrix4.hpp"
#include "Mesh.hpp"
#include <vector>

const int FPS = 30;
const int TARGET_FRAME_TIME = 1000 / FPS;

enum CullMethod {
    CULL_NONE,
    CULL_BACKFACE
};

class RedWoodEngine {
    private:
        Display* display;
        bool isRunning;
        int previousFrameTime;
        double deltaTime;

        CullMethod cullMethod;

        Vec3 cameraPosition;
        double fov;
        double aspectRatio;
        double zNear;
        double zFar;

        Mesh mesh;

        std::vector<Triangle> trianglesToRender;
        Matrix4 matrixGenerator;
        Matrix4 worldMatrix;
        Matrix4 projectionMatrix;
        Matrix4 viewMatrix;

    public:
        // produce a fullscreen window
        RedWoodEngine();

        // set a custom window height and width
        RedWoodEngine(int windowWidth, int windowHeight);

        ~RedWoodEngine();

        void run();
    
    private:
        void setup();

        void processInput();

        void update();

        void render();

        void setDefaultCamera();
};

#endif // __RED_WOOD_ENGINE_HPP__