#ifndef CUP_H
#define CUP_H

#include "ultrasonic.h"

class Cup : public Ultrasonic {
    
    public:
        Cup(int trigPin, int echoPin)
            : Ultrasonic(trigPin, echoPin) {}

        bool checkCup() {
            float distance = this->getDistanceMm();

            for(int i = 0; i < 5; i++){
                distance = this->getDistanceMm();
                if(distance < 300) break;
            }

            return distance < 70;    
        }

        ~Cup(){}
};

#endif //CUP_H
