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
    Spaceship* spaceship = new Spaceship(width/2,height/2,50,90, 0, 0);
    Missile* missile = new Missile(spaceship->GetX(), spaceship->GetY(), 20, 0,10);

    while (true) {
        int input = fw->GetInput();
        if (input == SDLK_ESCAPE) {
            std::cout << "Terminé";
            exit(0);
        }

        spaceship->Move(width,height);

        switch(input) {
            case SDLK_UP:
                std::cout << "up";
                spaceship->SpeedUp(2);
                break;
            case SDLK_DOWN:
                std::cout << "down";
                spaceship->SpeedDown(2);
                break;
            case SDLK_LEFT:
                std::cout << "left";
                spaceship->Rotate(-10);
                break;
            case SDLK_RIGHT:
                std::cout << "right";
                spaceship->Rotate(10);
                break;

            case SDLK_SPACE :
                if(missile != nullptr) {
                    fw->DrawMissile(spaceship->GetX(), spaceship->GetY());
                    if(missile->Move(width, height)) {
                        delete missile;
                        missile = nullptr;
                    }
                }
                break;
        }

        if(asteroid != nullptr) {
            fw->DrawAsteroid(asteroid->GetX(), asteroid->GetY(), asteroid->GetSize());
            asteroid->SetXSpeed(10);
            asteroid->Move(width, height);
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

        fw->DrawShip(spaceship->GetX(), spaceship->GetY(), spaceship->GetAngle(), 1, false);
        fw->Update();
    }
}
