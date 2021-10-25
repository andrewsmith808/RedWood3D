#ifndef __DISPLAY_HPP__
#define __DISPLAY_HPP__

#include <SDL2/SDL.h>

class Display {
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
        Display();

        // set a custom window height and width
        Display(int windowWidth, int windowHeight);

        bool initializeWindow();

        void render();

        void processInput();

        void setup();

        void renderColorBuffer();

        void clearColorBuffer(unsigned int color);

};


#endif