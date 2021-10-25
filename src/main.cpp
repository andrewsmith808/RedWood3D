#include "RedWoodEngine.hpp"

int main() {

    RedWoodEngine* instance = new RedWoodEngine(1920, 1080);

    instance->run();

    delete instance;

    return 0;
}