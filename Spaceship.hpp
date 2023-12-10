#ifndef CPP_PROJECT_SPACESHIP_HPP
#define CPP_PROJECT_SPACESHIP_HPP
#include "FlyingObject.hpp"
class Spaceship : public FlyingObject {
private:
    double angle;
    double xSpeed;
    double ySpeed;
    int shieldLevel;
    bool warnUser;
    bool isInvulnerable;
    int invulnerabilityTimer;

public:
    ///////////////
    // Constructeur
    // -------
    // * x, y : coordonnées du centre de l'astéroïde, en pixels
    // * size : diamètre du vaisseau
    // * angle d'orientation
    Spaceship(double x, double y, double size, double angle);

    Spaceship(double x, double y, double size, double angle, double xSpeed, double ySpeed);

    //////////
    // Getters
    double GetAngle() const;

    int GetShieldLevel();

    bool GetWarnUser() const;

    bool GetIsInvulnerable() const;

    ///////////////////////
    // Accélère le vaisseau
    // -------
    // * accelerationFactor : le facteur d'accéleration appliqué
    void SpeedUp(double accelerationFactor);

    ///////////////////////
    // Décélère le vaisseau
    // -------
    // * decelerationFactor : le facteur de décéleration appliqué
    void SpeedDown(double decelerationFactor);

    void limitTheSpeed();

    ///////////////////////////
    // Fait pivoter le vaisseau
    // -------
    // * angle : l'angle de rotation, en degrés.
    void Rotate(double rAngle);

    void Move(double screenWidth, double screenHeight);

    void Move();

    void destroyShield();

    void hitByAnAsteroid();

    void updateState(int delaTime);
};

#endif //CPP_PROJECT_SPACESHIP_HPP
