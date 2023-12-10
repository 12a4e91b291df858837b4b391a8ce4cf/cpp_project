#include <iostream>
#include <random>
#include <vector>
#include "framework.hpp"
#include "Asteroid.hpp"
#include "Missile.hpp"
#include "Spaceship.hpp"
#include <algorithm>

#define MAX_ASTEROIDS 5

int main(int argc, char* argv[]) {
    Framework* fw = new Framework(100, 60, 20);
    int width = fw->GetScreenWidth();
    int height = fw->GetScreenHeight();

    //generation aléatoire
    std::random_device random;
    std::mt19937 gen(random());

    std::vector<Asteroid*> asteroids; //stockage

    //Asteroid* asteroid = new Asteroid(0, 0, 100, 2, 2);
    Spaceship* spaceship = new Spaceship(width/2,height/2,50,90, 0, 0);
    Missile* missile = nullptr;
    int compteur = 0;

    while (true) {
        // DÉPLACEMENT
        spaceship->Move(width,height);

        if(missile != nullptr) {
            if(missile->Move(width, height)) {
                delete missile;
                missile = nullptr;
            }
        }

        for(auto& asteroid : asteroids) {
            asteroid->Move(width, height);
        }

        //COLLISION
        for (size_t i = 0; i < asteroids.size(); ++i) {
            if (missile != nullptr && asteroids[i] != nullptr) {
                if (FlyingObject::Collide(*asteroids[i], *missile)) {
                    std::cout << "Collision Detected" << std::endl;

                    asteroids[i]->setIsCollided(true);
                    delete asteroids[i];
                    asteroids.erase(asteroids.begin() + i);
                    --i;// pour pas que la liste soit décalée
                    //asteroids[i] = nullptr;

                    std::cout << "numbers of remaning asteroids :" << asteroids.size() << std::endl;

                    delete missile;
                    missile = nullptr;
                    break;
                }
            }
        }

        //CREATION DES ASTEROIDES
        while(compteur < MAX_ASTEROIDS) {
            std::uniform_int_distribution<> zoneDistr(0, 7);
            int zone = zoneDistr(gen);
            if (zone >= 4) zone++;

            int gridX = zone % 3;
            int gridY = zone / 3;
            std::uniform_real_distribution<> xDistr(gridX * width / 3, (gridX + 1) * width / 3);
            std::uniform_real_distribution<> yDistr(gridY * height / 3, (gridY + 1) * height / 3);

            double asteroidX = xDistr(gen);
            double asteroidY = yDistr(gen);
            std::uniform_int_distribution<> angleDistr(-180, 180);
            int asteroidAngle = angleDistr(gen);

            double asteroidSpeed = 2;//vitesse fixe ou random
            double asteroidXSpeed = asteroidSpeed * std::cos(asteroidAngle * M_PI / 180.0);
            double asteroidYSpeed = asteroidSpeed * std::sin(asteroidAngle * M_PI / 180.0);

            asteroids.push_back(new Asteroid(asteroidX, asteroidY, 100, asteroidXSpeed, asteroidYSpeed));
            compteur++;
        }

        // AFFICHAGE
        fw->DrawShip(spaceship->GetX(), spaceship->GetY(), spaceship->GetAngle(), 1, false);

        for (size_t i = 0; i < asteroids.size(); ++i) {
            if (asteroids[i] != nullptr && !asteroids[i]->GetIsCollided()) {
                fw->DrawAsteroid(asteroids[i]->GetX(), asteroids[i]->GetY(), asteroids[i]->GetSize());
            }
        }

        if(missile != nullptr) { //peut pas dessiner si c'est un nul pointeur
            fw->DrawMissile(missile->GetX(), missile->GetY());
        }

        // CLAVIER
        int input = fw->GetInput();
        if (input == SDLK_ESCAPE || asteroids.empty()) {
            std::cout << "Terminé";
            exit(0);
        }

        switch(input) {
            case SDLK_UP:
                spaceship->SpeedUp(0.15);
                break;
            case SDLK_DOWN:
                spaceship->SpeedDown(0.15);
                break;
            case SDLK_LEFT:
                spaceship->Rotate(-10);
                break;
            case SDLK_RIGHT:
                spaceship->Rotate(10);
                break;
            case SDLK_SPACE :
                if(missile == nullptr) {
                    missile = new Missile(spaceship->GetX(), spaceship->GetY(), 20, 10,spaceship->GetAngle());
                }
                break;
        }

        fw->Update();
    }
}
