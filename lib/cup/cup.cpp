#include "cup.h"

Cup::Cup(int trigPin, int echoPin)
        : Ultrasonic(trigPin, echoPin) {}

bool Cup::checkCup() {
    if (this->getDistanceMm() < 50) return true;
    return false;
}