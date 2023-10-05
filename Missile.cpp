#include "Missile.hpp"
#include <cmath>

Missile::Missile(double x, double y, double size, double speed, double angle) : FlyingObject(x, y, size) {
    this->speed = speed;
    this->angle = angle;
}

bool Missile::Move(double screenWidth, double screenHeight) {
    double angleRad = angle * M_PI / 180.0 - (M_PI / 2); // On retire Pi/2 parce que dès que on initialise le spaceship considère que 0 = Pi/2 donc il faut retirer pi/2 pour se retrouver à la bonne inclinaison
    SetX(GetX() + speed * cos(angleRad));
    SetY(GetY() + speed * sin(angleRad));

    if( GetX() > screenWidth || GetY() > screenHeight
         || GetX() < 0  || GetY() < 0 ) {
        return true;
    }

    return false;
}
