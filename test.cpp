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

    Asteroid* asteroid = new Asteroid(0, 0, 100, 2, 2);
    Spaceship* spaceship = new Spaceship(width/2,height/2,50,90, 0, 0);
    Missile* missile = nullptr;

    while (true) {
        // DÉPLACEMENT
        spaceship->Move(width,height);

        if(missile != nullptr) {
            if(missile->Move(width, height)) {
                delete missile;
                missile = nullptr;
            }
        }

        if(asteroid != nullptr) {
            asteroid->SetXSpeed(10);
            asteroid->Move(width, height);
        }

        //COLLISION
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

        // AFFICHAGE
        fw->DrawShip(spaceship->GetX(), spaceship->GetY(), spaceship->GetAngle(), 1, false);

        if(asteroid != nullptr) {
            fw->DrawAsteroid(asteroid->GetX(), asteroid->GetY(), asteroid->GetSize());
        }

        if(missile != nullptr) { //peut pas dessiner si c'est un nul pointeur
            fw->DrawMissile(missile->GetX(), missile->GetY());
        }

        // CLAVIER
        int input = fw->GetInput();
        if (input == SDLK_ESCAPE) {
            std::cout << "Terminé";
            exit(0);
        }

        switch(input) {
            case SDLK_UP:
                std::cout << "up";
                spaceship->SpeedUp(0.15);
                break;
            case SDLK_DOWN:
                std::cout << "down";
                spaceship->SpeedDown(0.15);
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
                if(missile == nullptr) {
                    missile = new Missile(spaceship->GetX(), spaceship->GetY(), 20, 60,spaceship->GetAngle());
                }
                break;
        }

        fw->Update();
    }
}
