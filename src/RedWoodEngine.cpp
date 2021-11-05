#include "RedWoodEngine.hpp"
#include <cmath>

RedWoodEngine::RedWoodEngine() {
    // Set width and height of the SDL window with the max screen resolution
    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);
    display = new Display(display_mode.w, display_mode.h);
    isRunning = false;

    setDefaultCamera();

    fov = M_PI / 3.0;
    aspectRatio = (double)display->getWindowHeight() / (double)display->getWindowWidth();
    zNear = 1.0;
    zFar = 20.0;
}

RedWoodEngine::RedWoodEngine(int windowWidth, int windowHeight) {
    display = new Display(windowWidth, windowHeight);
    isRunning = false;

    setDefaultCamera();

    fov = M_PI / 3.0;
    aspectRatio = (double)display->getWindowHeight() / (double)display->getWindowWidth();
    zNear = 1.0;
    zFar = 20.0;
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

void RedWoodEngine::setup() {
    display->setup();

    projectionMatrix = generator.perspective(fov, aspectRatio, zNear, zFar);
}

void RedWoodEngine::run() {
    isRunning = display->initializeWindow();

    setup();

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

}