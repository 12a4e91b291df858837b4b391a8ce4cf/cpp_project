#include "Asteroid.hpp"

Asteroid::Asteroid(double x, double y, double size, double xSpeed, double ySpeed) {
    this->x = x;
    this->y = y;
    this->size = size;
    this->xSpeed = xSpeed;
    this->ySpeed = ySpeed;

}

double Asteroid::GetX() {
    return this->x;
}

double Asteroid::GetY() {
    return this->y;
}

double Asteroid::GetXSpeed() {
    return this->xSpeed;
}

double Asteroid::GetYSpeed() {
    return this->ySpeed;
}

double Asteroid::GetSize() {
    return this->size;
}

void Asteroid::SetX(double x) {
    this->x = x;
}

void Asteroid::SetY(double y) {
    this->y = y;
}

void Asteroid::SetXSpeed(double xSpeed) {
    this->xSpeed = xSpeed;
}

void Asteroid::SetYSpeed(double ySpeed) {
    this->ySpeed = ySpeed;
}

void Asteroid::SetSize(double size) {
    this->size = size;
}

void Asteroid::Move() {
    x += xSpeed;
    y += ySpeed;
}

///////////////////////////////////////
// Déplacement de l'objet avec réentrée
// déplace selon le vecteur de vitesse de l'objet
// en cas de sortie des limites de l'écran, fait réapparaitre l'objet
// de l'autre côté
// -------
// * screenWidth, screenHeight : taille de l'écran
void Asteroid::Move(double screenWidth, double screenHeight) {
    Move();
    x = (int) (x + screenWidth) % (int) screenWidth;
    y = (int) (y + screenHeight) % (int) screenHeight;
}