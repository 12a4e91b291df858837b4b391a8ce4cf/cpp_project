#include "controller.hpp"
#include <iostream>
#define NUMBER_OF_DESIRED_ASTEROIDS 5

Controller::Controller(int fps, int shipSize, int missileSize) {
    this->framework = new Framework(fps, shipSize, missileSize);
    this->model = new Model(framework->GetScreenWidth(), framework->GetScreenHeight());
    this->view = new View(fps, shipSize, missileSize);
};

void Controller::LaunchGame() {
    model->createAsteroids(NUMBER_OF_DESIRED_ASTEROIDS);

    //Boucle principale du jeu
    while(true) {
        model->updateStateOfSpaceship();

        model->moveSpaceshipAndMissile();
        model->moveAsteroids();

        model->collideBetweenAsteroidsAndMissiles();
        model->collideBetweenAsteroidsAndSpaceship();

        view->drawObjects(model->getAllFlyingObjects());

        int input = framework->GetInput();
        if (input == SDLK_ESCAPE || model->isShieldLevelBelowZero()) {
            std::cout << "GAME FINISHED, YOU LOST";
            exit(0);
        } else if (model->isAsteroidEmpty()) {
            std::cout << "GAME FINISHED, YOU WON";
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

        view->updateDisplay();
    }
}
