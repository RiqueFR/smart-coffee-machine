#ifndef CUP_H
#define CUP_H

#include <ultrasonic.h>

class Cup : public Ultrasonic {
    
    public:
        Cup(int trigPin, int echoPin);

        bool checkCup();
};

#endif //CUP_H