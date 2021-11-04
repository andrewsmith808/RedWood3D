#include "RedWoodEngine.hpp"

// temporary test variables : MAKE SURE TO DELETE 
color_t lineColor = {0xFFFFFFFF};
color_t rectColor = {0xFFFF8972};

RedWoodEngine::RedWoodEngine() {
    // Set width and height of the SDL window with the max screen resolution
    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);
    display = new Display(display_mode.w, display_mode.h);
    isRunning = false;

    setDefaultCamera();
}

RedWoodEngine::RedWoodEngine(int windowWidth, int windowHeight) {
    display = new Display(windowWidth, windowHeight);
    isRunning = false;

    setDefaultCamera();
}

RedWoodEngine::~RedWoodEngine() {
    delete display;
    SDL_Quit();
}

void RedWoodEngine::setDefaultCamera() {
    Vec3 pos(0, 0, 0);
    Vec3 dir(0, 0, 1);
    Vec3 v(0, 0, 0);

    camera.position = pos;
    camera.direction = dir;
    camera.forward_velocity = v;
    camera.yaw = 0.0;
}

void RedWoodEngine::run() {
    isRunning = display->initializeWindow();

    display->setup();

    while(isRunning) {
        processInput();
        update();
        display->render();
    }
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

void RedWoodEngine::update() {
    display->drawGrid();
    display->drawLine(0, 1920, 0, 1080, lineColor);
    display->drawRect(960, 540, 100, 200, rectColor);
}



