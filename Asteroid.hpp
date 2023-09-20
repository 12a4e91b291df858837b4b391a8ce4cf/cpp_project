#ifndef CPP_PROJECT_ASTEROID_HPP
#define CPP_PROJECT_ASTEROID_HPP


#include "FlyingObject.hpp"

class Asteroid : public FlyingObject {
    private:
        double xSpeed;
        double ySpeed;

    public:
        Asteroid(double x, double y, double size, double xSpeed, double ySpeed);
        void Move();
        void Move(double screenWidth, double screenHeight);
        double GetXSpeed() const;
        double GetYSpeed() const;
        void SetXSpeed(double xSpeed);
        void SetYSpeed(double ySpeed);
};


#endif //CPP_PROJECT_ASTEROID_HPP
