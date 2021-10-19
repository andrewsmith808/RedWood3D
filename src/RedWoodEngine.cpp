#include "RedWoodEngine.hpp"

RedWoodEngine::RedWoodEngine() {
    // Set width and height of the SDL window with the max screen resolution
    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);
    windowWidth = display_mode.w;
    windowHeight = display_mode.h;
    isRunning = false;
    colorBuffer = nullptr;
    colorBufferTexture = nullptr;
}

RedWoodEngine::RedWoodEngine(int windowWidth, int windowHeight) :
    windowWidth(windowWidth),
    windowHeight(windowHeight),
    window(nullptr),
    renderer(nullptr),
    isRunning(false),
    colorBuffer(nullptr),
    colorBufferTexture(nullptr) {}

RedWoodEngine::~RedWoodEngine() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void RedWoodEngine::run() {
    
    isRunning = initializeWindow();

    while(isRunning) {
        processInput();
        render();
    }

}

bool RedWoodEngine::initializeWindow() {
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

void RedWoodEngine::render() {
    SDL_RenderClear(renderer);

    renderColorBuffer();

    SDL_RenderPresent(renderer);
}

void RedWoodEngine::processInput() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
				    isRunning = false;
				    break;
                }            
            default:
                break;
        }
    }
}

void RedWoodEngine::setup() {

    // allocate memory for the color buffer
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

void RedWoodEngine::renderColorBuffer() {
    SDL_UpdateTexture(
        colorBufferTexture,
        nullptr,
        colorBuffer,
        (int)(windowWidth * sizeof(unsigned int))
    );
    SDL_RenderCopy(renderer, colorBufferTexture, nullptr, nullptr);
}

void RedWoodEngine::clearColorBuffer(unsigned int color) {
    for (int height = 0; height < windowHeight; height++) {
        for (int width = 0; width < windowWidth; width++) {
            colorBuffer[(windowWidth * height) + width] = color;
        }
    }

}

