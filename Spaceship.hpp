#ifndef CPP_PROJECT_SPACESHIP_HPP
#define CPP_PROJECT_SPACESHIP_HPP
#include "FlyingObject.hpp"
class Spaceship : public FlyingObject {
private:
    double angle;
        double xSpeed;
        double ySpeed;
    public:
    ///////////////
    // Constructeur
    // -------
    // * x, y : coordonnées du centre de l'astéroïde, en pixels
    // * size : diamètre du vaisseau
    // * angle d'orientation
    Spaceship(double x, double y, double size, double angle);

    //////////
    // Getters
    double GetAngle() const;

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

    ///////////////////////////
    // Fait pivoter le vaisseau
    // -------
    // * angle : l'angle de rotation, en degrés.
    void Rotate(double rAngle);

    void Move(double screenWidth, double screenHeight);

    void Move();
};

#endif //CPP_PROJECT_SPACESHIP_HPP