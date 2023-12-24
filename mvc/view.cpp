#include "view.hpp"

View::View(int fps, int shipSize, int missileSize) {
    this->framework = new Framework(fps, shipSize, missileSize);
};

void View::drawObjects(std::vector<FlyingObject *> flyingObjects) {
    for(const auto& object : flyingObjects) {
        if(object != nullptr) {
            std::string typeName = object->getTypeName();
            if(typeName == "Spaceship") {
                auto spaceship = dynamic_cast<Spaceship*> (object);
                drawSpaceship(spaceship);
            } else if (typeName == "Missile") {
                auto missile = dynamic_cast<Missile*> (object);
                drawMissile(missile);
            } else if (typeName == "Asteroid") {
                auto asteroid = dynamic_cast<Asteroid*> (object);
                drawAsteroids(asteroid);
            }
        }
    }
}

void View::updateDisplay(){
    this->framework->Update();
}

void View::drawSpaceship(Spaceship* spaceship) {
    framework->DrawShip(spaceship->GetX(), spaceship->GetY(), spaceship->GetAngle(), spaceship->GetShieldLevel(), spaceship->GetWarnUser());
}

void View::drawAsteroids(Asteroid* asteroid) {
    if (asteroid != nullptr || !asteroid->GetIsCollided()) {
        framework->DrawAsteroid(asteroid->GetX(), asteroid->GetY(), asteroid->GetSize());
    }
}

void View::drawMissile(Missile* missile) {
    if(missile != nullptr) { //peut pas dessiner si c'est un nul pointeur
        framework->DrawMissile(missile->GetX(), missile->GetY());
    }
}