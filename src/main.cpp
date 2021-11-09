#include "RedWoodEngine.hpp"
#include "Vec.hpp"
#include "Matrix4.hpp"
#include <iostream>

int main() {

    RedWoodEngine* instance = new RedWoodEngine(1920, 1200);

    instance->run();

    delete instance;
    return 0;
}