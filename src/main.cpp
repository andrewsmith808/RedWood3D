#include "RedWoodEngine.hpp"
#include "Vec.hpp"
#include "Matrix4.hpp"
#include <iostream>

int main() {

    RedWoodEngine* instance = new RedWoodEngine(1920, 1080);

    instance->run();

    delete instance;

    // ---------------------------------
    // Some simple tests for Matrix4
    // ---------------------------------

    Matrix4 testOutput;
    std::cout << testOutput << std::endl;

    Matrix4 testIdentityMultiplication;
    Matrix4 m;
    Matrix4 result = testIdentityMultiplication.mulMatrix(m);
    std::cout << result << std::endl;
    

    return 0;
}