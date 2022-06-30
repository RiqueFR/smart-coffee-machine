#include "cup.h"

Cup::Cup(int trigPin, int echoPin)
        : Ultrasonic(trigPin, echoPin) {}

bool Cup::checkCup() {
    float distance = this->getDistanceMm();

    while(distance > 300){
        distance = this->getDistanceMm();
    }
    
    return distance < 50;    
}