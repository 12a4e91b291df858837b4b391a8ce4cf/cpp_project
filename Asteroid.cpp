#include "Asteroid.hpp"
#include <random>
#include <vector>
#include <iostream>

#define NUMBER_OF_ASTEROIDS_AFTER_DIVISION 3
#define MINIMUM_SIZE 50

///////////////////////////////////////
// Déplacement de l'objet avec réentrée
// déplace selon le vecteur de vitesse de l'objet
// en cas de sortie des limites de l'écran, fait réapparaitre l'objet
// de l'autre côté
// -------
// * screenWidth, screenHeight : taille de l'écran
std::random_device random;
std::mt19937 gen(random());

std::vector<Asteroid*> asteroids;

void Asteroid::Move(double screenWidth, double screenHeight) {
    Move();

    if (GetX() < 0) {
        SetX(screenWidth + GetX());
    } else if (GetX() > screenWidth) {
        SetX(GetX() - screenWidth);
    }

    if (GetY() < 0) {
        SetY(screenHeight + GetY());
    } else if (GetY() > screenHeight) {
        SetY(GetY() - screenHeight);
    }
}

void Asteroid::Move() {
    SetX(GetX() + xSpeed);
    SetY(GetY() + ySpeed);
}


void Asteroid::SetXSpeed(double xSpeed) {
    this->xSpeed = xSpeed;
}

void Asteroid::SetYSpeed(double ySpeed) {
    this->ySpeed = ySpeed;
}

Asteroid::Asteroid(double x, double y, double size, double xSpeed, double ySpeed) : FlyingObject(x, y, size) {
    this->xSpeed = xSpeed;
    this->ySpeed = ySpeed;
}

double Asteroid::GetXSpeed() const {
    return this->xSpeed;
}

double Asteroid::GetYSpeed() const {
    return this->ySpeed;
}

bool Asteroid::GetIsCollided() const {
    return this->isCollided;
};

void Asteroid::setIsCollided(bool status) {
    this->isCollided = status;
}

void Asteroid::divideIntoMultipleAsteroids(std::vector<Asteroid*>& asteroidsList) {
    if (this->isCollided) {
        for (int i = 0; i < NUMBER_OF_ASTEROIDS_AFTER_DIVISION ; ++i) {
            double newSizeOfAsteroid = this->GetSize() / 2;

            std::uniform_int_distribution<> angleDistr(-180, 180);
            int asteroidAngle = angleDistr(gen);
            double newAsteroidSpeedFactor = 1.5;

            double asteroidXSpeed = newAsteroidSpeedFactor * std::cos(asteroidAngle * M_PI / 180.0);
            double asteroidYSpeed = newAsteroidSpeedFactor * std::sin(asteroidAngle * M_PI / 180.0);

            std::cout << "Creating new asteroids from asteroid at: " << this->GetX() << ", " << this->GetY() << std::endl;
            asteroidsList.push_back(new Asteroid(this->GetX(), this->GetY(), newSizeOfAsteroid, asteroidXSpeed, asteroidYSpeed));
            std::cout << "New asteroids count: " << asteroidsList.size() << std::endl;
        }
    } else
        std::cout << "too small" << std::endl;
}
