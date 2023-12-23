#include "model.hpp"
#include "../components/Spaceship.hpp"
#include "../components/Missile.hpp"

Model::Model(int width, int height) {
    this->width = width;
    this->height = height;
    this->spaceship = new Spaceship(width/2,height/2,50,90, 0, 0);
    this->missile = nullptr;
    const int MAX_ASTEROIDS = 100;
    this->lastTime = std::chrono::high_resolution_clock::now();
}

int Model::GetWidth() {
    return this->width;
}

int Model::GetHeight() {
    return this->height;
}

void Model::speedUp(double accelerationFactor) {
    spaceship->SpeedUp(accelerationFactor);
}

void Model::speedDown(double decelerationFactor) {
    spaceship->SpeedDown(decelerationFactor);
}

void Model::rotate(double rAngle) {
    spaceship->Rotate(rAngle);
}

void Model::updateGame(){
    this->framework->Update();
}

void Model::createMissile() {
    if(missile == nullptr) {
        missile = new Missile(spaceship->GetX(), spaceship->GetY(), 20, 10,spaceship->GetAngle());
    }
}

void Model::updateStateOfSpaceship() {
    auto currentTime = std::chrono::high_resolution_clock::now();
    float deltaTime = std::chrono::duration<float, std::milli>(currentTime - lastTime).count();
    lastTime = currentTime;

    spaceship->updateState(deltaTime);
}

