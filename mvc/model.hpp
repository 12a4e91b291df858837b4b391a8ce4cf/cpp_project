#ifndef CPP_PROJECT_MODEL_HPP
#define CPP_PROJECT_MODEL_HPP
#include "../components/FlyingObject.hpp"
#include "../components/Spaceship.hpp"
#include "../components/Missile.hpp"
#include "../components/Asteroid.hpp"
#include "../framework/Framework.hpp"
#include <random>
#include <vector>
#include <chrono>
#include <algorithm>

class Model {
    private:
        int width;
        int height;
        Spaceship* spaceship;
        Missile* missile;
        Framework* framework;
        std::chrono::high_resolution_clock::time_point lastTime;
        std::vector<Asteroid*> asteroids;
        std::mt19937 gen;
        std::vector<FlyingObject*> flyingObjects;


public:
        Model(int width, int height);

        void speedUp(double accelerationFactor);
        void speedDown(double decelerationFactor);
        void rotate(double rAngle);
        void createMissile();
        void updateStateOfSpaceship();
        void createAsteroids(int numberOfDesiredAsteroids);
        void moveSpaceshipAndMissile();
        void moveAsteroids();
        void collideBetweenAsteroidsAndMissiles();
        void collideBetweenAsteroidsAndSpaceship();
        bool isAsteroidEmpty();
        bool isShieldLevelBelowZero();
        int GetWidth();
        int GetHeight();
        std::vector<FlyingObject*> getAllFlyingObjects();

};





















#endif //CPP_PROJECT_MODEL_HPP
