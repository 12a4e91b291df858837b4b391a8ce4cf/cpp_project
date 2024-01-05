#include "model.hpp"
#include <iostream>
#define MINIMUM_SIZE_FOR_ASTEROID 50
#define MAX_ASTEROIDS 100

Model::Model(int width, int height) {
    this->width = width;
    this->height = height;
    this->spaceship = new Spaceship(width/2,height/2,50,90, 0, 0);
    flyingObjects.push_back(spaceship);
    this->missile = nullptr;
    this->lastTime = std::chrono::high_resolution_clock::now();
}

int Model::GetWidth() {
    return this->width;
}

int Model::GetHeight() {
    return this->height;
}

std::vector<FlyingObject *> Model::getAllFlyingObjects() {
    return this->flyingObjects;
}

bool Model::isAsteroidEmpty() {
    if(asteroids.empty()) {
        return true;
    } else {
        return false;
    }
}

bool Model::isShieldLevelBelowZero() {
    if(spaceship->GetShieldLevel() < 0) {
        return true;
    } else {
        return false;
    }
}

void Model::speedUp(double accelerationFactor) {
    spaceship->SpeedUp(accelerationFactor);
}

void Model::speedDown(double decelerationFactor) {
    spaceship->SpeedDown(decelerationFactor);
}

void Model::rotate(double rAngle) {
    spaceship->Rotate(rAngle);
}

void Model::createMissile() {
    if(missile == nullptr) {
        missile = new Missile(spaceship->GetX(), spaceship->GetY(), 20, 10,spaceship->GetAngle());
        flyingObjects.push_back(missile);
    }
}

void Model::createAsteroids(int numberOfDesiredAsteroids) {
    int asteroidsCreated = 0;
    const int possibleAsteroidSizes[] = {100,150,200};
    while (asteroidsCreated < numberOfDesiredAsteroids && asteroids.size() < MAX_ASTEROIDS) {
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
        double asteroidXSpeed = asteroidSpeed * std::cos(asteroidAngle * M_PI / 180.0);double asteroidYSpeed = asteroidSpeed * std::sin(asteroidAngle * M_PI / 180.0);

        int randomIndexForSize = rand() % 3;

        auto newAsteroid = new Asteroid(asteroidX, asteroidY, possibleAsteroidSizes[randomIndexForSize], asteroidXSpeed, asteroidYSpeed);
        asteroids.push_back(newAsteroid);
        flyingObjects.push_back(newAsteroid);
        asteroidsCreated++;
    }
}

void Model::updateStateOfSpaceship() {
    auto currentTime = std::chrono::high_resolution_clock::now();
    float deltaTime = std::chrono::duration<float, std::milli>(currentTime - lastTime).count();
    lastTime = currentTime;

    spaceship->updateState(deltaTime);
}

void Model::moveSpaceshipAndMissile() {
    spaceship->Move(width,height);

    if(missile != nullptr) {
        if(missile->Move(width, height)) {
            auto it2 = std::find(flyingObjects.begin(), flyingObjects.end(), missile);
            if (it2 != flyingObjects.end()) {
                flyingObjects.erase(it2);
            }

            delete missile;
            missile = nullptr;
        }
    }
}

void Model::moveAsteroids() {
    for(auto& asteroid : asteroids) {
        asteroid->Move(width, height);
    }
}

void Model::collideBetweenAsteroidsAndMissiles() {
    for (size_t i = 0; i < asteroids.size(); ++i) {
        if (missile != nullptr && asteroids[i] != nullptr) {
            if (FlyingObject::Collide(*asteroids[i], *missile)) {
                asteroids[i]->setIsCollided(true);
                if (asteroids[i]->GetSize() > (long) MINIMUM_SIZE_FOR_ASTEROID) {
                    std::vector<Asteroid*> newAsteroids;
                    asteroids[i]->divideIntoMultipleAsteroids(newAsteroids);
                    for (Asteroid* newAsteroid : newAsteroids) {
                        if (asteroids.size() < MAX_ASTEROIDS) {
                            asteroids.push_back(newAsteroid);
                            flyingObjects.push_back(newAsteroid);
                        } else {
                            delete newAsteroid; // Important pour éviter les fuites de mémoire
                        }
                    }
                }
                // Supprimer de flyingObjects
                auto it = std::find(flyingObjects.begin(), flyingObjects.end(), asteroids[i]);
                if (it != flyingObjects.end()) {
                    flyingObjects.erase(it);
                }

                delete asteroids[i];
                asteroids.erase(asteroids.begin() + i);
                --i;

                auto it2 = std::find(flyingObjects.begin(), flyingObjects.end(), missile);
                if (it2 != flyingObjects.end()) {
                    flyingObjects.erase(it2);
                }
                delete missile;
                missile = nullptr;
                break;
            }
        }
    }
}

void Model::collideBetweenAsteroidsAndSpaceship() {
    for (size_t i = 0; i < asteroids.size(); i++) {
        if(asteroids[i] != nullptr) {
            if(FlyingObject::Collide(*asteroids[i], *spaceship) && !spaceship->GetIsInvulnerable()) {
                spaceship->destroyShield();
                spaceship->hitByAnAsteroid();
                std::cout << "Spaceship hit, Shield level : " << spaceship->GetShieldLevel() + 1<< std::endl;

                asteroids[i]->setIsCollided(true);
                if (asteroids[i]->GetSize() > (long) MINIMUM_SIZE_FOR_ASTEROID) {
                    std::vector<Asteroid*> newAsteroids;
                    asteroids[i]->divideIntoMultipleAsteroids(newAsteroids);
                    for (Asteroid* newAsteroid : newAsteroids) {
                        if (asteroids.size() < MAX_ASTEROIDS) {
                            asteroids.push_back(newAsteroid);
                            flyingObjects.push_back(newAsteroid);
                        } else {
                            delete newAsteroid; // Important pour éviter les fuites de mémoire
                        }
                    }
                }
                // Supprimer de flyingObjects
                auto it = std::find(flyingObjects.begin(), flyingObjects.end(), asteroids[i]);
                if (it != flyingObjects.end()) {
                    flyingObjects.erase(it);
                }

                delete asteroids[i];
                asteroids.erase(asteroids.begin() + i);
                --i;
            }
        }
    }
}