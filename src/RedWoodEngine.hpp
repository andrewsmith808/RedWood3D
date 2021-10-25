#ifndef __RED_WOOD_ENGINE_HPP__
#define __RED_WOOD_ENGINE_HPP__

#include "Display.hpp"

const int FPS = 30;
const int TARGET_FRAME_TIME = 1000 / FPS;

class RedWoodEngine {
    private:
        Display* display;
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
};

#endif // __RED_WOOD_ENGINE_HPP__