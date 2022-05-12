#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>


class Button {
    private:
        int pin;
        int bouncerTime;
        bool pressed;
        bool stable;
        bool unstable;
    
    public:
        Button(int pin);

        bool changed();

        bool wasPressed();

        ~Button();
};

#endif //BUTTON_H