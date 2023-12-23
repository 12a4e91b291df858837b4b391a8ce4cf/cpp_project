#include "FlyingObject.hpp"
#include <cmath>

FlyingObject::FlyingObject(double x, double y, double size) {
    this->x = x;
    this->y = y;
    this->size = size;

}

double FlyingObject::GetX() {
    return this->x;
}

double FlyingObject::GetY() {
    return this->y;
}


double FlyingObject::GetSize() {
    return this->size;
}

void FlyingObject::SetX(double x) {
    this->x = x;
}

void FlyingObject::SetY(double y) {
    this->y = y;
}

void FlyingObject::SetSize(double size) {
    this->size = size;
}

bool FlyingObject::Collide(FlyingObject o1, FlyingObject o2) {
    double differenceBetweenX = o1.GetX() - o2.GetX();
    double differenceBetweenY = o1.GetY() - o2.GetY();
    double distanceBetweenFlyingObjectsCenter = sqrt(pow(differenceBetweenX,2) + pow(differenceBetweenY,2));
    return distanceBetweenFlyingObjectsCenter < (o1.GetSize()/2 + o2.GetSize()/2);
}

std::string FlyingObject::getTypeName() {
    return "";
}


