#ifndef __RED_WOOD_ENGINE_HPP__
#define __RED_WOOD_ENGINE_HPP__

#include "Display.hpp"
#include "Vec.hpp"

const int FPS = 30;
const int TARGET_FRAME_TIME = 1000 / FPS;

typedef struct {
    Vec3 position;
    Vec3 direction;
    Vec3 forward_velocity;
    double yaw;
} camera_t;

class RedWoodEngine {
    private:
        Display* display;
        camera_t camera;
        bool isRunning;

    public:
        // produce a fullscreen window
        RedWoodEngine();

        // set a custom window height and width
        RedWoodEngine(int windowWidth, int windowHeight);

        ~RedWoodEngine();

        void run();
    
    private:
        void processInput();

        void update();

        void setDefaultCamera();
};

#endif // __RED_WOOD_ENGINE_HPP__