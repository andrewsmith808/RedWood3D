#include "RedWoodEngine.hpp"

int main() {

    RedWoodEngine* instance = new RedWoodEngine();

    instance->initializeWindow();

    delete instance;

    return 0;
}