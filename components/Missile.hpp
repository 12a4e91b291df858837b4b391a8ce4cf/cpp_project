#ifndef CPP_PROJECT_MISSILE_HPP
#define CPP_PROJECT_MISSILE_HPP


#include "FlyingObject.hpp"

class Missile : public FlyingObject {
    private:
        double speed;
        double angle;

    public:
        // Constructeur
        // * x, y : position dans l'écran
        // * size : diamètre du missile
        // * speed : vitesse de déplacement
        // * angle : orientation
        Missile(double x, double y, double size, double speed, double angle);

        // déplace selon les vitesses de déplacement de l'objet
        // -------
        // Renvoie : un booléen indiquant s'il y a sortie des limites de l'écran
        bool Move(double screenWidth, double screenHeight);

        std::string getTypeName() override;

        //GETTERS

        //SETTERS

};



#endif //CPP_PROJECT_MISSILE_HPP
