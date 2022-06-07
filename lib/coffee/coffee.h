#ifndef COFFEE_H
#define COFFEE_H

#include <ultrasonic.h>

#include <button.h>
#include <cup.h>
#include <ultrasonic.h>
#include <Wire.h> // 0x3F
#include <LiquidCrystal_I2C.h>

class Coffee : public Ultrasonic {
    private:
        int maxCupAmount = 30;

        const int trigPinCup = 18;
        const int echoPinCup = 5;
        const int trigPinWat = 32;
        const int echoPinWat = 35;

        const int buttonRequestPin = 25; // laranja
        const int buttonAddCupPin = 26; // azul
        const int buttonRemoveCupPin = 27;

        int ledBuiltIn = 2;

        int actualQtdCup = 0;
        int requestedCups = 0;

        const int mmToCups = 30;
        const int maxMm = 200;

        const int portaReleBomba = 2;
        const int portaReleCoffe = 12;

        bool buttonRequestPressed = false;

        // set the LCD number of columns and rows
        int lcdColumns = 16;
        int lcdRows = 2;

        LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x3F, lcdColumns, lcdRows);

        Ultrasonic ultrasonic = Ultrasonic(this->trigPinWat, this->echoPinWat);;
        Cup cup = Cup(this->trigPinCup, this->echoPinCup);
        Button buttonRequest = Button(this->buttonRequestPin);
        Button buttonAddCup = Button(this->buttonAddCupPin);
        Button buttonRemoveCup = Button(this->buttonRemoveCupPin);;
    
    public:
        Coffee(int maxCupAmount);

        void setup();

        void loop();
};

#endif //COFFEE_H