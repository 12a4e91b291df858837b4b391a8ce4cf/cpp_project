#ifndef CPP_PROJECT_FLYINGOBJECT_HPP
#define CPP_PROJECT_FLYINGOBJECT_HPP


class FlyingObject {
    private:
        double x;
        double y;
        double size;


    public:
        // Getters
        virtual double GetX();
        virtual double GetY();
        virtual double GetSize();


        // Setters
        virtual void SetX(double x);
        virtual void SetY(double y);
        void SetSize(double size);

        FlyingObject(double x, double y, double size);

        /////////////////////////////
        // Détermination de collision
        // calcul basé sur l'hypothèse que les objets sont sphériques
        // -------
        // * o1, o2 : les deux objets à tester
        // -------
        // Renvoie : true si les deux objets se touchent, false sinon
        static bool Collide(FlyingObject o1, FlyingObject o2);

};


#endif //CPP_PROJECT_FLYINGOBJECT_HPP
