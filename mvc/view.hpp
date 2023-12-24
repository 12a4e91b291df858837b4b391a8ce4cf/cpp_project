#ifndef CPP_PROJECT_VIEW_HPP
#define CPP_PROJECT_VIEW_HPP
#include "../framework/Framework.hpp"
#include "../components/FlyingObject.hpp"
#include "../components/Spaceship.hpp"
#include "../components/Missile.hpp"
#include "../components/Asteroid.hpp"

class View {
    private:
        Framework* framework;

    public:
        View(int fps, int shipSize, int missileSize);

        void drawObjects(std::vector<FlyingObject*> flyingObjects);

        void updateDisplay();

        void drawSpaceship(Spaceship* spaceship);

        void drawAsteroids(Asteroid* asteroid);

        void drawMissile(Missile* missile);
};





















#endif //CPP_PROJECT_VIEW_HPP
