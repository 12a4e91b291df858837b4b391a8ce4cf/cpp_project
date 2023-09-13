#ifndef CPP_PROJECT_ASTEROID_HPP
#define CPP_PROJECT_ASTEROID_HPP


class Asteroid {
    private:
        double x;
        double y;
        double size;
        double xSpeed;
        double ySpeed;

    public:
    // Getters
    double GetX();
    double GetY();
    double GetXSpeed();
    double GetYSpeed();
    double GetSize();


    // Setters
    void SetX(double xSpeed);
    void SetY(double ySpeed);
    void SetXSpeed(double xSpeed);
    void SetYSpeed(double ySpeed);
    void SetSize(double size);


    // Constructeur
    // -------
    // * x, y : position dans l'écran
    // * size : diamètre de l'objet
    // * xSpeed, ySpeed : vecteur de vitesse de l'objet
    Asteroid(double x, double y, double size, double xSpeed, double ySpeed);


    void Move();

    void Move(double screenWidth, double screenHeight);
};


#endif //CPP_PROJECT_ASTEROID_HPP
