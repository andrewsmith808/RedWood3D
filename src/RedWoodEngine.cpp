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

    cameraPosition.x = 0; cameraPosition.y = 0; cameraPosition.z = 0;
    fov = M_PI / 3.0;
    aspectRatio = (double)display->windowHeight / (double)display->windowWidth;
    zNear = 0.1;
    zFar = 100.0;

    light.direction.x = 0; light.direction.y = 0; light.direction.z = 1;
}

RedWoodEngine::RedWoodEngine(int windowWidth, int windowHeight) {
    display = new Display(windowWidth, windowHeight);
    isRunning = false;
    previousFrameTime = 0;
    deltaTime = 0;

    cameraPosition.x = 0; cameraPosition.y = 0; cameraPosition.z = 0;
    fov = M_PI / 3.0;
    aspectRatio = (double)display->windowHeight / (double)display->windowWidth;
    zNear = 0.1;
    zFar = 100.0;

    light.direction.x = 0; light.direction.y = 0; light.direction.z = 1;
}

RedWoodEngine::~RedWoodEngine() {
    delete display;
    SDL_Quit();
}

void RedWoodEngine::setup() {
    display->setup();

    cullMethod = CULL_BACKFACE;
    projectionMatrix = matrixGenerator.perspective(fov, aspectRatio, zNear, zFar);
    //std::cout << "projection matrix: " << std::endl << projectionMatrix << std::endl;
}

void RedWoodEngine::run() {
    isRunning = display->initializeWindow();

    setup();
    int numOfRuns = 50;
    while(isRunning) {
        processInput();
        update();
        render();
        numOfRuns--;
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

    previousFrameTime = SDL_GetTicks();

    //std::cout << "Triangles to render size: " << trianglesToRender.size() << std::endl;

    mesh.rotation.x += 0.007;
    mesh.rotation.y += 0.03;
    mesh.rotation.z += 0.004;
    mesh.translation.z = 5.0;

    Matrix4 scaleMatrix = matrixGenerator.scale(mesh.scale.x, mesh.scale.y, mesh.scale.z);
    //std::cout << "Scale Matrix Calculation: " << std::endl;
    //std::cout << scaleMatrix << std::endl;

    Matrix4 translationMatrix = matrixGenerator.translate(mesh.translation.x, mesh.translation.y, mesh.translation.z);
    //std::cout << "Translation Matrix Calculation: " << std::endl;
    //std::cout << translationMatrix << std::endl;

    Matrix4 rotationMatrixX = matrixGenerator.rotateX(mesh.rotation.x);
    //std::cout << "RoationX Matrix Calculation: " << std::endl;
    //std::cout << rotationMatrixX << std::endl;

    Matrix4 rotationMatrixY = matrixGenerator.rotateY(mesh.rotation.y);
    //std::cout << "RoationY Matrix Calculation: " << std::endl;
    //std::cout << rotationMatrixY << std::endl;

    Matrix4 rotationMatrixZ = matrixGenerator.rotateZ(mesh.rotation.z);
    //std::cout << "RotationZ Matrix Calculation: " << std::endl;
    //std::cout << rotationMatrixZ << std::endl;

    // Time to Loop through our mesh triangles!
    int numFaces = mesh.faces.size();
    for (int i = 0; i < numFaces; i++) {
        face_t meshFace = mesh.faces.at(i);

        Vec3 faceVerticies[3];
        faceVerticies[0] = mesh.verticies.at(meshFace.a - 1);
        faceVerticies[1] = mesh.verticies.at(meshFace.b - 1);
        faceVerticies[2] = mesh.verticies.at(meshFace.c - 1);

        Vec4 transformedVerticies[3];

        // loop through each verticie of the current face
        for (int j = 0; j < 3; j++) {
            Vec4 transformedVertex = Vec3_To_Vec4(faceVerticies[j]);

            worldMatrix.identity();
            
            worldMatrix = scaleMatrix.mulMatrix(worldMatrix);
            worldMatrix = rotationMatrixZ.mulMatrix(worldMatrix);
            worldMatrix = rotationMatrixY.mulMatrix(worldMatrix);
            worldMatrix = rotationMatrixX.mulMatrix(worldMatrix);
            worldMatrix = translationMatrix.mulMatrix(worldMatrix);

            //std::cout << "World Matrix calculation: " << i << "," << j << std::endl;
            //std::cout << worldMatrix << std::endl;

            transformedVertex = worldMatrix.mulVec4(transformedVertex);

            transformedVerticies[j] = transformedVertex;
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

        Vec3 cameraRay = cameraPosition.sub(a);

        double normalDotCameraRay = normal.dot(cameraRay);

        if (cullMethod == CULL_BACKFACE) {
            if (normalDotCameraRay < 0) {
                continue;
            } 
        }

        Vec4 projectedPoints[3];

        for (int j = 0; j < 3; j++) {
            projectedPoints[j] = projectionMatrix.mulProjection(transformedVerticies[j]);

            projectedPoints[j].x *= (display->windowWidth / 2.0);
            projectedPoints[j].y *= (display->windowHeight / 2.0);

            projectedPoints[j].x += (display->windowWidth / 2.0);
            projectedPoints[j].y += (display->windowHeight / 2.0);

            //std::cout << "Projected Points: " << i << "," << j << std::endl;
            //std::cout << projectedPoints[j] << std::endl;
        }

        Triangle projectedTriangle;

        double averageDepth = (transformedVerticies[0].z + transformedVerticies[1].z + transformedVerticies[2].z) / 3.0;

        // Calculate the shade intensity based on how aliged is the face normal and the opposite of the light direction
        double lightIntensity = -1 * normal.dot(light.direction);
        std::cout << "normal: " << normal << std::endl;
        std::cout << "Light Intensity: " << lightIntensity << std::endl;

        // Calculate the triangle color based on the light angle
        color_t triangleColor = applyLightIntensity(meshFace.color, lightIntensity);

        projectedTriangle.points[0].x = projectedPoints[0].x;
        projectedTriangle.points[0].y = projectedPoints[0].y;
        projectedTriangle.points[1].x = projectedPoints[1].x;
        projectedTriangle.points[1].y = projectedPoints[1].y;
        projectedTriangle.points[2].x = projectedPoints[2].x;
        projectedTriangle.points[2].y = projectedPoints[2].y;

        projectedTriangle.color = triangleColor;
        projectedTriangle.avgDepth = averageDepth;

        trianglesToRender.push_back(projectedTriangle);
    }

    for (int i = 0; i < trianglesToRender.size(); i++) {
        for (int j = i; j < trianglesToRender.size(); j++) {
            if (trianglesToRender.at(i).avgDepth < trianglesToRender.at(j).avgDepth) {
                Triangle temp = trianglesToRender.at(i);
                trianglesToRender.at(i) = trianglesToRender.at(j);
                trianglesToRender.at(j) = temp;
            }
        }
    }

    for (int i = 0; i < trianglesToRender.size(); i++) {
        //std::cout << "Triangle To Render: " << i << std::endl;
        //std::cout << trianglesToRender.at(i).points[0] << std::endl;
        //std::cout << trianglesToRender.at(i).points[1] << std::endl;
        //std::cout << trianglesToRender.at(i).points[2] << std::endl << std::endl;
    }
}

void RedWoodEngine::render() {
    color_t clearColor = {0xFF111111};

    SDL_RenderClear(display->renderer);

    display->drawGrid();    
    
    for (int i = 0; i < trianglesToRender.size(); i++) {
        Triangle triangle = trianglesToRender.at(i);

        triangle.drawFilledTriangle(display);
    }

    trianglesToRender.clear();

    display->renderColorBuffer();

    display->clearColorBuffer(clearColor);

    SDL_RenderPresent(display->renderer);
}

color_t RedWoodEngine::applyLightIntensity(color_t originalColor, double intensityFactor) {
    if (intensityFactor < 0)
        intensityFactor = 0;
    if (intensityFactor > 1) 
        intensityFactor = 1;

    color_t a = {originalColor.color & 0xFF000000};
    color_t r = {(originalColor.color & 0x00FF0000) * intensityFactor};
    color_t g = {(originalColor.color & 0x0000FF00) * intensityFactor};
    color_t b = {(originalColor.color & 0x000000FF) * intensityFactor};

    color_t newColor = {a.color | (r.color & 0x00FF0000) | (g.color & 0x0000FF00) | (b.color & 0x000000FF)};

    return newColor;
}
