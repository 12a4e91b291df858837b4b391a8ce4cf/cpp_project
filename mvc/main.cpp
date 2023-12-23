#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <algorithm>
#include "../framework/framework.hpp"
#include "../components/Asteroid.hpp"
#include "../components/Missile.hpp"
#include "../components/Spaceship.hpp"

#define MINIMUM_SIZE 50
//#define MAX_ASTEROIDS 5


int main(int argc, char* argv[]) {
    Framework* fw = new Framework(100, 60, 20);
    int width = fw->GetScreenWidth();
    int height = fw->GetScreenHeight();
    const int MAX_ASTEROIDS = 100;

    //generation aléatoire
    std::random_device random;
    std::mt19937 gen(random());

    std::vector<Asteroid*> asteroids; //stockage

    //instances
    Spaceship* spaceship = new Spaceship(width/2,height/2,50,90, 0, 0);
    Missile* missile = nullptr;

    //utilitaire
    auto lastTime = std::chrono::high_resolution_clock::now();
    int compteur = 0;

    while (true) {
        //CLOCK ACTUELLE ET CREATION DU DELTA TEMPS
        auto currentTime = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float, std::milli>(currentTime - lastTime).count();
        lastTime = currentTime;

        spaceship->updateState(deltaTime);

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

        //COLLISION ENTRE LES ASTEROIDES ET LES MISSILES
        for (size_t i = 0; i < asteroids.size(); ++i) {
            if (missile != nullptr && asteroids[i] != nullptr) {
                if (FlyingObject::Collide(*asteroids[i], *missile)) {
                    std::cout << "Collision Detected" << std::endl;
                    asteroids[i]->setIsCollided(true);
                    if (asteroids[i]->GetSize() > (long) MINIMUM_SIZE) {
                        asteroids[i]->divideIntoMultipleAsteroids(asteroids);
                    }
                    delete asteroids[i];
                    asteroids.erase(asteroids.begin() + i);
                    --i;

                    std::cout << "numbers of remaning asteroids :" << asteroids.size() << std::endl;

                    delete missile;
                    missile = nullptr;
                    break;
                }
            }
        }

        //COLLISION ENTRE LES ASTEROIDES ET LE SPACESHIP
        for (size_t i = 0; i < asteroids.size(); i++) {
            if(asteroids[i] != nullptr) {
                if(FlyingObject::Collide(*asteroids[i], *spaceship) && !spaceship->GetIsInvulnerable()) {
                    spaceship->destroyShield();
                    spaceship->hitByAnAsteroid();
                    std::cout << "Spaceship hit, Shield level :" << spaceship->GetShieldLevel() << std::endl;

                    asteroids[i]->setIsCollided(true);
                    delete asteroids[i];
                    asteroids[i] = nullptr;
                    asteroids.erase(asteroids.begin() + i);
                    --i;// pour pas que la liste soit décalée
                }
            }
        }

        //CREATION DES ASTEROIDES
        while(compteur < MAX_ASTEROIDS-95) {
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

            asteroids.push_back(new Asteroid(asteroidX, asteroidY, 200, asteroidXSpeed, asteroidYSpeed));
            compteur++;
        }

        // AFFICHAGE
        fw->DrawShip(spaceship->GetX(), spaceship->GetY(), spaceship->GetAngle(), spaceship->GetShieldLevel(), spaceship->GetWarnUser());


        for (size_t i = 0; i < asteroids.size(); ++i) {
            if (asteroids[i] != nullptr ||  !asteroids[i]->GetIsCollided()) {
                fw->DrawAsteroid(asteroids[i]->GetX(), asteroids[i]->GetY(), asteroids[i]->GetSize());
            }
        }


        if(missile != nullptr) { //peut pas dessiner si c'est un nul pointeur
            fw->DrawMissile(missile->GetX(), missile->GetY());
        }

        // CLAVIER
        int input = fw->GetInput();
        if (input == SDLK_ESCAPE || asteroids.empty() || spaceship->GetShieldLevel() < 0) {
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

 