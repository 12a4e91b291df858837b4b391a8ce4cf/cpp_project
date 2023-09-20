#include <iostream>
#include "framework.hpp"
#include "Asteroid.hpp"
#include "Missile.hpp"

int main(int argc, char* argv[]) {
    Framework* fw = new Framework(100, 60, 20);
    int width = fw->GetScreenWidth();
    int height = fw->GetScreenHeight();

    Asteroid* asteroid = new Asteroid(0, 0, 200, 2, 2);
    Missile* missile = new Missile(width/2, height/2, 100, 0,10);

    while (true) {
        if (fw->GetInput() == SDLK_ESCAPE) {
            std::cout << "Terminé";
            exit(0);
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

        fw->Update();
    }
}
