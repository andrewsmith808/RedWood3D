#include "Display.hpp"

Display::Display() {
    // Set width and height of the SDL window with the max screen resolution
    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);
    windowWidth = display_mode.w;
    windowHeight = display_mode.h;
    colorBuffer = nullptr;
    colorBufferTexture = nullptr;
}

Display::Display(int windowWidth, int windowHeight) :
    windowWidth(windowWidth),
    windowHeight(windowHeight),
    window(nullptr),
    renderer(nullptr),
    colorBuffer(nullptr),
    colorBufferTexture(nullptr) {}

Display::~Display() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    delete colorBuffer;
}

bool Display::initializeWindow() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    }

    // Create a SDL Window
    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_BORDERLESS
    );
    if (!window) {
        fprintf(stderr, "Error creating SDL window.\n");
        return false;
    }

    // Create a SDL renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "Error creating SDL renderer.\n");
        return false;
    }

    return true;
}

void Display::render() {
    color_t clearColor = {0xFF696969};

    SDL_RenderClear(renderer);

    renderColorBuffer();

    clearColorBuffer(clearColor);

    SDL_RenderPresent(renderer);
}

void Display::setup() {

    // allocate memory for the color buffer and z buffer
    colorBuffer = (unsigned int*)malloc(sizeof(unsigned int) * windowWidth * windowHeight);

    // Creating a SDL texture that is used to display the color buffer
    colorBufferTexture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA32,
        SDL_TEXTUREACCESS_STREAMING,
        windowWidth,
        windowHeight
    );
}

void Display::renderColorBuffer() {
    SDL_UpdateTexture(
        colorBufferTexture,
        nullptr,
        colorBuffer,
        (int)(windowWidth * sizeof(unsigned int))
    );
    SDL_RenderCopy(renderer, colorBufferTexture, nullptr, nullptr);
}

void Display::clearColorBuffer(color_t color) {
    for (int height = 0; height < windowHeight; height++) {
        for (int width = 0; width < windowWidth; width++) {
            colorBuffer[(windowWidth * height) + width] = color.color;
        }
    }

}

void Display::drawPixel(int x, int y, color_t pixelColor) {
    if (x >= 0 && x < windowWidth && y >= 0 && y < windowHeight) {
        colorBuffer[(windowWidth * y) + x] = pixelColor.color;
    }
}

void Display::drawGrid() {
    color_t gridColor = {0xFFFFFFFF};
    for (int y = 0; y < windowHeight; y += 50) {
        for (int x = 0; x < windowWidth; x += 50) {
            drawPixel(x, y, gridColor);
        }
    }
}

void Display::drawRect(int x, int y, int width, int height, color_t rectColor) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int currX = x + i;
            int currY = y + j;
            drawPixel(currX, currY, rectColor);
        }
    }
}

void Display::drawLine(int x0, int y0, int x1, int y1, color_t lineColor) {
    int deltaX = x1 - x0;
    int deltaY = y1 - y0;

    int longestSide = 0;

    if (abs(deltaX) >= abs(deltaY))
        longestSide = abs(deltaX);
    else
        longestSide = abs(deltaY);
    
    double dx = deltaX / double(longestSide);
    double dy = deltaY / double(longestSide);

    double currX = x0;
    double currY = y0;

    for (int i = 0; i <= longestSide; i++) {
        drawPixel(round(currX), round(currY), lineColor);
        currX += dx;
        currY += dy;
    }
}