#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>


class Button {
    private:
        int pin;
        unsigned long debounceTime;
        unsigned long lastBebounceTime;
        int status;
        int lastStatus;
    
    public:
        Button(int pin);

        bool wasPressed();

        ~Button();
};

#endif //BUTTON_H