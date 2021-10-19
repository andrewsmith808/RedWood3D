#include "RedWoodEngine.hpp"

RedWoodEngine::RedWoodEngine() {
    // Set width and height of the SDL window with the max screen resolution
    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);
    windowWidth = display_mode.w;
    windowHeight = display_mode.h;
    isRunning = false;
}

RedWoodEngine::RedWoodEngine(int windowWidth, int windowHeight) :
    windowWidth(windowWidth),
    windowHeight(windowHeight),
    window(nullptr),
    renderer(nullptr),
    isRunning(false) {}

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
    SDL_SetRenderDrawColor(renderer, 69, 69, 69, 69);
    SDL_RenderClear(renderer);

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
