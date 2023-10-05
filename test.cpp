#include <iostream>
#include "framework.hpp"
#include "Asteroid.hpp"
#include "Missile.hpp"
#include "Spaceship.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    Framework* fw = new Framework(100, 60, 20);
    int width = fw->GetScreenWidth();
    int height = fw->GetScreenHeight();

    Asteroid* asteroid = new Asteroid(0, 0, 200, 5, 2);
    Missile* missile = new Missile(width/2, height/2, 20, 0,10);
    Spaceship* spaceship = new Spaceship(width/2,height/2,50,90);

    while (true) {
        int input = fw->GetInput();
        if (input == SDLK_ESCAPE) {
            std::cout << "Terminé";
            exit(0);
        }

        switch(input) {
            case SDLK_UP:
                std::cout << "up";
                spaceship->SpeedUp(5);
                break;
            case SDLK_DOWN:
                std::cout << "down";
                spaceship->SpeedDown(5);
                break;
            case SDLK_LEFT:
                std::cout << "left";
                spaceship->Rotate(-5);
                break;
            case SDLK_RIGHT:
                std::cout << "right";
                spaceship->Rotate(5);
                break;
        }

        if(asteroid != nullptr) {
            fw->DrawAsteroid(asteroid->GetX(), asteroid->GetY(), asteroid->GetSize());
            asteroid->SetXSpeed(10);
            asteroid->Move(width, height);
        }

        if(missile != nullptr) {
            fw->DrawMissile(missile->GetX(), missile->GetY());
            if(missile->Move(width, height)) {
                delete missile;
                missile = nullptr;
            }
        }

        if ((asteroid != nullptr) && (missile != nullptr)) {
            if (FlyingObject::Collide(*asteroid, *missile)) {
                std::cout << "Collision Detected" << std::endl;
                delete asteroid;
                asteroid = nullptr;
                delete missile;
                missile = nullptr;
                std::cout << "Objects deleted" << std::endl;
            }
        }

        if(spaceship != nullptr) {
            fw->DrawShip(spaceship->GetX(), spaceship->GetY(), spaceship->GetAngle(), 0, false);
        }

        spaceship->Move(width,height);
        fw->Update();
    }
}
