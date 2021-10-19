#ifndef __RED_WOOD_ENGINE_HPP__
#define __RED_WOOD_ENGINE_HPP__

#include <SDL2/SDL.h>

class RedWoodEngine {
    private:
        int windowWidth;
        int windowHeight;

        SDL_Window* window;
        SDL_Renderer* renderer;

        bool isRunning;

        unsigned int* colorBuffer;
        SDL_Texture* colorBufferTexture;

    public:
        // produce a fullscreen window
        RedWoodEngine();

        // set a custom window height and width
        RedWoodEngine(int windowWidth, int windowHeight);

        ~RedWoodEngine();

        void run();
    
    private:
        bool initializeWindow();

        void render();

        void processInput();

        void setup();
};

#endif // __RED_WOOD_ENGINE_HPP__