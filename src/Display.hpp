#ifndef __DISPLAY_HPP__
#define __DISPLAY_HPP__

#include <SDL2/SDL.h>

const int DEFAULT_PIXEL_COLOR = 0xFFFFFFFF;

typedef struct {
    unsigned int color;
} color_t;

class Display {
    private:
        int windowWidth;
        int windowHeight;

        SDL_Window* window;
        SDL_Renderer* renderer;

        unsigned int* colorBuffer;
        SDL_Texture* colorBufferTexture;
    public:
        // produce a fullscreen window
        Display();

        // set a custom window height and width
        Display(int windowWidth, int windowHeight);

        ~Display();

        bool initializeWindow();

        void render();

        void setup();

        void renderColorBuffer();

        void clearColorBuffer(color_t color);

        void drawPixel(int x, int y, color_t pixelColor);

        void drawGrid();

        void drawRect(int x, int y, int width, int height, color_t rectColor);

        void drawLine(int x0, int x1, int y0, int y1, color_t lineColor);


};


#endif