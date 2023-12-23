#include "controller.hpp"
#include <iostream>

Controller::Controller(int fps, int shipSize, int missileSize) {
    this->framework = new Framework(fps, shipSize, missileSize);
    //this->model = new Model();
    //this->view = new View();
};

void Controller::LaunchGame() {
    this->model = new Model(framework->GetScreenWidth(), framework->GetScreenHeight());

    while(true) {
        model->updateStateOfSpaceship();

        int input = framework->GetInput();
        /*
        if (input == SDLK_ESCAPE || asteroids.empty() || spaceship->GetShieldLevel() < 0) {
            std::cout << "Terminé";
            exit(0);
        }
         */
        if (input == SDLK_ESCAPE) {
            std::cout << "Terminé";
            exit(0);
        }

        switch(input) {
            case SDLK_UP:
                model->speedUp(0.15);
                break;
            case SDLK_DOWN:
                model->speedDown(0.15);
                break;
            case SDLK_LEFT:
                model->rotate(-10);
                break;
            case SDLK_RIGHT:
                model->rotate(10);
                break;
            case SDLK_SPACE :
                model->createMissile();
                break;

        }

        model->updateGame();
    }
}
