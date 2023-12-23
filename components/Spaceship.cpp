#include <cmath>
#include "Spaceship.hpp"
#define MAX_SPEED 5.0

using namespace std;

Spaceship::Spaceship(double x, double y, double size, double angle, double xSpeed, double ySpeed) : FlyingObject(x,y,size) {
    this->xSpeed = xSpeed;
    this->ySpeed = ySpeed;
    this->angle = angle;
    this->shieldLevel = 2;
}

double Spaceship::GetAngle() const {
    return this->angle;
}

int Spaceship::GetShieldLevel() {
    return this->shieldLevel;
}

bool Spaceship::GetIsInvulnerable() const {
    return this->isInvulnerable;
}

bool Spaceship::GetWarnUser() const {
    return this->warnUser;
}

void Spaceship::Move(double screenWidth, double screenHeight) {
    //double angleRad = M_PI*(this->angle-90)/180;
    SetX(GetX() + xSpeed);
    SetY(GetY() + ySpeed);

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

void Spaceship::SpeedUp(double accelerationFactor) {
    double angleInRadian = M_PI*(this->angle-90)/180;
    double horizontalAcceleration = cos(angleInRadian) * accelerationFactor;
    double verticalAcceleration = sin(angleInRadian) * accelerationFactor;

    this->xSpeed += horizontalAcceleration;
    this->ySpeed += verticalAcceleration;

    limitTheSpeed();
}

void Spaceship::SpeedDown(double decelerationFactor) {
    double angleInRadian = M_PI*(this->angle-90)/180;
    double horizontalAcceleration = cos(angleInRadian) * (-decelerationFactor);
    double verticalAcceleration = sin(angleInRadian) * (-decelerationFactor);

    this->xSpeed += horizontalAcceleration;
    this->ySpeed += verticalAcceleration;

    limitTheSpeed();
}

void Spaceship::limitTheSpeed() {
    double currentSpeed = sqrt(xSpeed * xSpeed + ySpeed * ySpeed);
    if (currentSpeed > MAX_SPEED) {
        double scaleTheSpeedToMAX_SPEED = MAX_SPEED/currentSpeed;
        xSpeed *= scaleTheSpeedToMAX_SPEED;
        ySpeed *= scaleTheSpeedToMAX_SPEED;
    }
}

void Spaceship::Rotate(double rAngle) {
    this->angle = (int) (this->angle + rAngle) % 360;
}

void Spaceship::destroyShield() {
    shieldLevel--;
}

void Spaceship::hitByAnAsteroid() {
    warnUser = true;

    if(!isInvulnerable) {
        isInvulnerable = true;
        invulnerabilityTimer = 3000;
    }
}

void Spaceship::updateState(int delaTime) {
    if(warnUser) {
        invulnerabilityTimer-=delaTime;
        if(invulnerabilityTimer <= 0) {
            warnUser = false;
            isInvulnerable = false;
        }
    }
}

std::string Spaceship::getTypeName() {
    return "Spaceship";
}

