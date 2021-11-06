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

    cullMethod = CULL_NONE;
    projectionMatrix = matrixGenerator.perspective(fov, aspectRatio, zNear, zFar);
}

void RedWoodEngine::run() {
    isRunning = display->initializeWindow();

    setup();

    //int countDown = 2;

    while(isRunning) {
        processInput();
        update();
        render();
        //countDown--;
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

    trianglesToRender.clear();

    mesh.rotation.setX(mesh.rotation.getX() + (0.0 * deltaTime));
    mesh.rotation.setY(mesh.rotation.getY() + (0.0 * deltaTime));
    mesh.rotation.setZ(mesh.rotation.getZ() + (0.0 * deltaTime));
    mesh.translation.setZ(25.0);

    //std::cout << "mesh rotation: " << mesh.rotation.getX() << " " << mesh.rotation.getY() << " " << mesh.rotation.getZ() << std::endl;

    Vec3 target(0, 0, 1);
    Matrix4 cameraYawRotation = matrixGenerator.rotateY(camera.yaw);

    Vec4 yawMulTarget = cameraYawRotation.mulVec4(Vec3_To_Vec4(target));
    camera.direction = Vec4_To_Vec3(yawMulTarget);

    target = camera.position.add(camera.direction);
    Vec3 upDirection(0, 1, 0);

    viewMatrix = matrixGenerator.lookAt(camera.position, target, upDirection);

    Matrix4 scaleMatrix = matrixGenerator.scale(mesh.scale.getX(),
                                                mesh.scale.getY(),
                                                mesh.scale.getY());

    Matrix4 translationMatrix = matrixGenerator.translate(mesh.translation.getX(),
                                                          mesh.translation.getY(),
                                                          mesh.translation.getZ());

    Matrix4 rotationMatrixX = matrixGenerator.rotateX(mesh.rotation.getX());
    Matrix4 rotationMatrixY = matrixGenerator.rotateY(mesh.rotation.getY());
    Matrix4 rotationMatrixZ = matrixGenerator.rotateZ(mesh.rotation.getZ());

    // Time to Loop through our mesh triangles!
    int numFaces = mesh.faces.size();
    for (int i = 0; i < numFaces; i++) {
        face_t meshFace = mesh.faces.at(i);
        //std::cout << "Mesh: " << meshFace.a << " " << meshFace.b << " " << meshFace.c << std::endl;

        Vec3 faceVerticies[3];
        faceVerticies[0] = mesh.verticies.at(meshFace.a - 1);
        faceVerticies[1] = mesh.verticies.at(meshFace.b - 1);
        faceVerticies[2] = mesh.verticies.at(meshFace.c - 1);

        Vec4 transformedVerticies[3];

        // loop through each verticie of the current face
        for (int j = 0; j < 3; j++) {
            Vec4 transformedVertex = Vec3_To_Vec4(faceVerticies[j]);
            
            worldMatrix = scaleMatrix.mulMatrix(worldMatrix);
            worldMatrix = rotationMatrixZ.mulMatrix(worldMatrix);
            worldMatrix = rotationMatrixY.mulMatrix(worldMatrix);
            worldMatrix = rotationMatrixX.mulMatrix(worldMatrix);
            worldMatrix = translationMatrix.mulMatrix(worldMatrix);

            //std::cout << worldMatrix << std::endl;

            transformedVertex = worldMatrix.mulVec4(transformedVertex);
            transformedVertex = viewMatrix.mulVec4(transformedVertex);

            transformedVerticies[j] = transformedVertex;
            //std::cout << "transformed vertex " << j << ": " << transformedVertex.getX() << " " << transformedVertex.getY() << " " << transformedVertex.getZ() << " " << transformedVertex.getW() << std::endl;
        }

        Vec3 a = Vec4_To_Vec3(transformedVerticies[0]);
        Vec3 b = Vec4_To_Vec3(transformedVerticies[1]);
        Vec3 c = Vec4_To_Vec3(transformedVerticies[2]);

        Vec3 ab = b.sub(a);
        Vec3 ac = c.sub(a);
        ab.normalize();
        ac.normalize();

        Vec3 normal = ab.cross(ac);
        normal.normalize();

        Vec3 origin(0, 0, 0);
        Vec3 cameraRay = origin.sub(a);

        double normalDotCameraRay = normal.dot(cameraRay);

        if (cullMethod == CULL_BACKFACE) {
            if (normalDotCameraRay < 0) {
                continue;
            } 
        }

        Vec4 projectedPoints[3];

        for (int j = 0; j < 3; j++) {
            projectedPoints[j] = projectionMatrix.mulVec4(transformedVerticies[j]);

            if (projectedPoints[j].getW() != 0) {
                projectedPoints[j].setX(projectedPoints[j].getX() / projectedPoints[j].getW());
                projectedPoints[j].setY(projectedPoints[j].getY() / projectedPoints[j].getW());
                projectedPoints[j].setZ(projectedPoints[j].getZ() / projectedPoints[j].getW());
            }

            projectedPoints[j].setY(projectedPoints[j].getY() * -1);

            projectedPoints[j].setX(projectedPoints[j].getX() * (display->getWindowWidth() / 2.0));
            projectedPoints[j].setY(projectedPoints[j].getY() * (display->getWindowHeight() / 2.0));

            projectedPoints[j].setX(projectedPoints[j].getX() + (display->getWindowWidth() / 2.0));
            projectedPoints[j].setY(projectedPoints[j].getY() + (display->getWindowHeight() / 2.0));

            std::cout << "projected points: " << projectedPoints[j].getX() << " " << projectedPoints[j].getY() << " " << projectedPoints[j].getZ() << " " << projectedPoints[j].getW() << std::endl;
        }

        Triangle projectedTriangle;
        color_t triangleColor = {0xFF000000};

        projectedTriangle.points[0] = projectedPoints[0];
        projectedTriangle.points[1] = projectedPoints[1];
        projectedTriangle.points[2] = projectedPoints[2];
        projectedTriangle.color = triangleColor;

        trianglesToRender.push_back(projectedTriangle);
    }
}

void RedWoodEngine::render() {
    color_t clearColor = {0xFFFFFFFF};

    SDL_RenderClear(display->getRender());

    display->drawGrid();

    // std::cout << "Triangles to Render: " << trianglesToRender.size() << std::endl;
    
    for (int i = 0; i < trianglesToRender.size(); i++) {
        Triangle triangle = trianglesToRender.at(i);

        triangle.drawFilledTriangle(display);
    }

    display->renderColorBuffer();

    display->clearColorBuffer(clearColor);

    display->clearZBuffer();

    SDL_RenderPresent(display->getRender());
}