#ifndef CPP_PROJECT_CONTROLLER_HPP
#define CPP_PROJECT_CONTROLLER_HPP
#include "../framework/framework.hpp"
#include "model.hpp"
#include "view.hpp"


class Controller {
    private:
        View* view;
        Model* model;
        Framework* framework;



    public:
        Controller(int fps, int shipSize, int missileSize);
        void LaunchGame();
};












#endif //CPP_PROJECT_CONTROLLER_HPP
