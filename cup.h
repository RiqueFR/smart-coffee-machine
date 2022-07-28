#ifndef CUP_H
#define CUP_H

#include "ultrasonic.h"

class Cup : public Ultrasonic {
    
    public:
        Cup(int trigPin, int echoPin)
            : Ultrasonic(trigPin, echoPin) {}

        bool checkCup() {
            float distance = this->getDistanceMm();

            while(distance > 300){
                distance = this->getDistanceMm();
            }

            return distance < 50;    
        }

        ~Cup(){}
};

#endif //CUP_H
