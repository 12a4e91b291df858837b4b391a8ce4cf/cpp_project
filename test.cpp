#include <iostream>
#include <random>
#include <vector>
#include "framework.hpp"
#include "Asteroid.hpp"
#include "Missile.hpp"
#include "Spaceship.hpp"

#define MAX_ASTEROIDS 15

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

                    // Suppression et nettoyage de l'astéroïde
                    delete asteroids[i];
                    asteroids.erase(asteroids.begin() + i); // Retire l'astéroïde de la liste
                    --i; // Ajustez l'indice après avoir retiré un élément

                    // Suppression et nettoyage du missile
                    delete missile;
                    missile = nullptr;

                    std::cout << "Objects deleted" << std::endl;

                    break; // Sortez de la boucle si une collision a été traitée
                }
            }
        }

        //CREATION DES ASTEROIDES
        if (asteroids.size() < MAX_ASTEROIDS) {  // MAX_ASTEROIDS est à définir en fonction de votre jeu
            std::uniform_int_distribution<> zoneDistr(0, 7);
            int zone = zoneDistr(gen);
            if (zone >= 4) zone++;  // Ajuster pour le trou central

            // Déterminer les coordonnées basées sur la zone
            int gridX = zone % 3;
            int gridY = zone / 3;
            std::uniform_real_distribution<> xDistr(gridX * width / 3, (gridX + 1) * width / 3);
            std::uniform_real_distribution<> yDistr(gridY * height / 3, (gridY + 1) * height / 3);

            double asteroidX = xDistr(gen);
            double asteroidY = yDistr(gen);
            std::uniform_int_distribution<> angleDistr(-180, 180);
            int asteroidAngle = angleDistr(gen);

            double asteroidSpeed = 2;  // La vitesse peut être fixe ou aléatoire
            double asteroidXSpeed = asteroidSpeed * std::cos(asteroidAngle * M_PI / 180.0);
            double asteroidYSpeed = asteroidSpeed * std::sin(asteroidAngle * M_PI / 180.0);

            asteroids.push_back(new Asteroid(asteroidX, asteroidY, 100, asteroidXSpeed, asteroidYSpeed));
        }


        // AFFICHAGE
        fw->DrawShip(spaceship->GetX(), spaceship->GetY(), spaceship->GetAngle(), 1, false);

        /*
        if(asteroid != nullptr) {
            fw->DrawAsteroid(asteroid->GetX(), asteroid->GetY(), asteroid->GetSize());
        }
        */
        for (auto & asteroid : asteroids) {
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
                    missile = new Missile(spaceship->GetX(), spaceship->GetY(), 20, 10,spaceship->GetAngle());
                }
                break;
        }

        fw->Update();
    }
}
