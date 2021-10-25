#ifndef __RED_WOOD_ENGINE_HPP__
#define __RED_WOOD_ENGINE_HPP__

#include "Display.hpp"

const int FPS = 30;
const int TARGET_FRAME_TIME = 1000 / FPS;

class RedWoodEngine {
    private:
        // int windowWidth;
        // int windowHeight;

        // SDL_Window* window;
        // SDL_Renderer* renderer;

        // bool isRunning;

        // unsigned int* colorBuffer;
        // SDL_Texture* colorBufferTexture;

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
    //     bool initializeWindow();

    //     void render();

        void processInput();

    //     void setup();

    //     void renderColorBuffer();

    //     void clearColorBuffer(unsigned int color);
};

#endif // __RED_WOOD_ENGINE_HPP__