#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "esphome.h"

//define sound speed in mm/uS
#define SOUND_SPEED 0.34

class Ultrasonic {
    private:
        int trigPin;
        int echoPin;

    public:
        Ultrasonic() {};

        Ultrasonic(int trigPin, int echoPin) {
            this->trigPin = trigPin;
            this->echoPin = echoPin;

            pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
            pinMode(echoPin, INPUT); // Sets the echoPin as an Input
        }

        float getDistanceMm() {
            // Clears the trigPin
            digitalWrite(trigPin, LOW);
            delayMicroseconds(2);
            // Sets the trigPin on HIGH state for 10 micro seconds
            digitalWrite(trigPin, HIGH);
            delayMicroseconds(10);
            digitalWrite(trigPin, LOW);

            // Reads the echoPin, returns the sound wave travel time in microseconds
            double duration = pulseIn(echoPin, HIGH);

            // Calculate the distance
            return duration * SOUND_SPEED/2;
        }


        ~Ultrasonic(){}
};

#endif //ULTRASONIC_H
