#include "RedWoodEngine.hpp"
#include <iostream>
#include <cmath>

RedWoodEngine::RedWoodEngine() {
    // Set width and height of the SDL window with the max screen resolution
    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);
    display = new Display(display_mode.w, display_mode.h);
    isRunning = false;
    previousFrameTime = 0;
    deltaTime = 0;

    setDefaultCamera();

    fov = M_PI / 3.0;
    aspectRatio = (double)display->getWindowHeight() / (double)display->getWindowWidth();
    zNear = 1.0;
    zFar = 20.0;
}

RedWoodEngine::RedWoodEngine(int windowWidth, int windowHeight) {
    display = new Display(windowWidth, windowHeight);
    isRunning = false;
    previousFrameTime = 0;
    deltaTime = 0;

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

    projectionMatrix = matrixGenerator.perspective(fov, aspectRatio, zNear, zFar);
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
    int waitTime = TARGET_FRAME_TIME - (SDL_GetTicks() - previousFrameTime);

    if (waitTime > 0 && waitTime <= TARGET_FRAME_TIME) {
        SDL_Delay(waitTime);
    }

    deltaTime = (SDL_GetTicks() - previousFrameTime) / 1000.0;
    previousFrameTime = SDL_GetTicks();

    mesh.setRoationAll(0.01 * deltaTime, 0.01 * deltaTime, 0.01 * deltaTime);
    mesh.setTranslationZ(5.0);

    Vec3 target(0, 0, 1);
    Matrix4 cameraYawRotation = matrixGenerator.rotateY(camera.yaw);

    Vec4 yawMulTarget = cameraYawRotation.mulVec4(Vec3_To_Vec4(target));
    camera.direction = Vec4_To_Vec3(yawMulTarget);

    target = camera.position.add(camera.direction);
    Vec3 upDirection(0, 1, 0);

    viewMatrix = matrixGenerator.lookAt(camera.position, target, upDirection);

    Matrix4 scaleMatrix = matrixGenerator.scale(mesh.getScaleX(),
                                                mesh.getScaleY(),
                                                mesh.getScaleZ());

    Matrix4 translationMatrix = matrixGenerator.translate(mesh.getTranslationX(),
                                                          mesh.getTranslationY(),
                                                          mesh.getTranslationZ());

    Matrix4 rotationMatrixX = matrixGenerator.rotateX(mesh.getRotationX());
    Matrix4 rotationMatrixY = matrixGenerator.rotateY(mesh.getRotationY());
    Matrix4 rotationMatrixZ = matrixGenerator.rotateY(mesh.getRotationZ());

    // Time to Loop through our mesh triangles!
}