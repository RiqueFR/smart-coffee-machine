#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>

//define sound speed in mm/uS
#define SOUND_SPEED 0.34

class Ultrasonic {
    private:
        int trigPin;
        int echoPin;
    
    public:
        Ultrasonic();

        Ultrasonic(int trigPin, int echoPin);

        float getDistanceMm();

        ~Ultrasonic();
};

#endif //ULTRASONIC_H