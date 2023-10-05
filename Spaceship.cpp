#include <cmath>
#include "Spaceship.hpp"
#include <iostream>
using namespace std;

Spaceship::Spaceship(double x, double y, double size, double angle, double xSpeed, double ySpeed) : FlyingObject(x,y,size) {
    this->xSpeed = xSpeed;
    this->ySpeed = ySpeed;
    this->angle = angle;
}

double Spaceship::GetAngle() const {
    return this->angle;
}

void Spaceship::Move(double screenWidth, double screenHeight) {
    double angleRad = M_PI*(this->angle-90)/180;
    SetX(GetX() + xSpeed * cos(angleRad));
    SetY(GetY() + ySpeed * sin(angleRad));

    if(GetX() < 0) {
        SetX(screenWidth);
    }
    else if(GetX() > screenWidth) {
        SetX(0);
    }

    if(GetY() < 0) {
        SetY(screenHeight);
    }
    else if(GetY() > screenHeight) {
        SetY(0);
    }

}

void Spaceship::Move() {
    SetX(GetX() + xSpeed);
    SetY(GetY() + ySpeed);
}


void Spaceship::SpeedUp(double accelerationFactor) {
    double angleInRadian = M_PI*(this->angle-90)/180;
    double horizontalAcceleration = cos(angleInRadian) * accelerationFactor;
    double verticalAcceleration = sin(angleInRadian) * accelerationFactor;

    this->xSpeed += horizontalAcceleration;
    this->ySpeed += verticalAcceleration;
}

void Spaceship::SpeedDown(double decelerationFactor) {
    double angleInRadian = M_PI*(this->angle-90)/180;
    double horizontalAcceleration = cos(angleInRadian) * decelerationFactor;
    double verticalAcceleration = sin(angleInRadian) * decelerationFactor;

    this->xSpeed += horizontalAcceleration;
    this->ySpeed += verticalAcceleration;
}

void Spaceship::Rotate(double rAngle) {
    this->angle = (int) (this->angle + rAngle) % 360;

}


