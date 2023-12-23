#ifndef CPP_PROJECT_MODEL_HPP
#define CPP_PROJECT_MODEL_HPP

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


public:
        Model(int width, int height);


        void speedUp(double accelerationFactor);
        void speedDown(double decelerationFactor);
        void rotate(double rAngle);
        void updateGame();
        void createMissile();
        void updateStateOfSpaceship();
        int GetWidth();
        int GetHeight();
};





















#endif //CPP_PROJECT_MODEL_HPP
