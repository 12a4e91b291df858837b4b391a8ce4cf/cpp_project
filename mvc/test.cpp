#include "../mvc/controller.hpp"


int main(int argc, char* argv[]) {
    auto* controller = new Controller(100, 60, 20);

    controller->LaunchGame();
}
