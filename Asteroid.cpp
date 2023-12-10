#include "Asteroid.hpp"

///////////////////////////////////////
// Déplacement de l'objet avec réentrée
// déplace selon le vecteur de vitesse de l'objet
// en cas de sortie des limites de l'écran, fait réapparaitre l'objet
// de l'autre côté
// -------
// * screenWidth, screenHeight : taille de l'écran
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
