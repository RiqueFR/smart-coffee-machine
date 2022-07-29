#ifndef COFFEE_H
#define COFFEE_H

#include "ultrasonic.h"

#include "button.h"
#include "cup.h"
#include "ultrasonic.h"
#include "Wire.h" // 0x3F
#include "LiquidCrystal_I2C.h"

class Coffee : public Ultrasonic {
    private:
        int maxCupAmount = 30;

        const int trigPinCup = 18;
        const int echoPinCup = 5;
        const int trigPinWat = 32;
        const int echoPinWat = 33;

        const int buttonRequestPin = 13; // laranja
        const int buttonAddCupPin = 12; // azul
        const int buttonRemoveCupPin = 14;

        int ledBuiltIn = 2;

        int actualQtdCup = 0;
        int requestedCups = 0;

        const int mmToCups = 30;
        const int maxMm = 200;

        const int portaReleBomba = 19;
        const int portaReleCoffe = 2;

        bool buttonRequestPressed = false;

        // set the LCD number of columns and rows
        int lcdColumns = 16;
        int lcdRows = 2;

        // slc -> 22
        // sla -> 21
        LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x3F, lcdColumns, lcdRows);

        Ultrasonic ultrasonic = Ultrasonic(this->trigPinWat, this->echoPinWat);
        Cup cup = Cup(this->trigPinCup, this->echoPinCup);

        MyButton buttonRequest = MyButton(25);
        MyButton buttonAddCup = MyButton(26);
        MyButton buttonRemoveCup = MyButton(27);

        bool hasCup = false;

        // states
        bool idle = true;
        bool fill = false;
        bool drain = false;
    
    public:
        Coffee(int maxCupAmount) {
            this->maxCupAmount = maxCupAmount;
        }

        void setup() {
            pinMode(portaReleBomba, OUTPUT);
            pinMode(portaReleCoffe, OUTPUT);
            pinMode(ledBuiltIn, OUTPUT);

            lcd.init();
            lcd.backlight();
        }


        // return true if the coffee maxine still needs to fill up
        bool fill_up() {
            float distanceMm;
            // check if the machine fill with the correct amount of cups
            if(actualQtdCup < requestedCups) {
                distanceMm = ultrasonic.getDistanceMm();

                lcd.setCursor(0,1);
                lcd.printf("Status: Enchendo");

                if(distanceMm > maxMm) {
                    return true;
                }

                ESP_LOGD("custom", "Enchendo reservatorio ++++++++++++++");
                ESP_LOGD("custom", "Distance (mm): %f", distanceMm);
                // Serial.print("Tem xícara: ");
                // ESP_LOGD("custom", hasCup);

                actualQtdCup = (maxMm - distanceMm) / mmToCups;
                ESP_LOGD("custom", "Quantidade atual de xícaras: %d", actualQtdCup);

                return true;
            }
            return false;
        }

        // return true if the coffee maxine still needs to drain out
        bool drain_out() {
            float distanceMm;
            // check if the machine emptied
            if(actualQtdCup > 0) {
                distanceMm = ultrasonic.getDistanceMm();

                lcd.setCursor(0,1);
                lcd.printf("Status: Coando  ");

                if(distanceMm > maxMm) {
                    return true;
                }

                ESP_LOGD("custom", "Esvaziando reservatorio -------------");
                ESP_LOGD("custom", "Distance (mm): %f", distanceMm);

                actualQtdCup = (maxMm - distanceMm) / mmToCups;
                ESP_LOGD("custom", "Quantidade atual de xícaras: %d", actualQtdCup);

                return true;
            }
            return false;
        }

        void loop() {
            if (buttonRequest.wasPressed() && !buttonRequestPressed && idle) {
                ESP_LOGD("custom", "Apertou o botão de request");
                buttonRequestPressed = true;
            }

            if(buttonRequestPressed && requestedCups == 0 && idle) {
                ESP_LOGD("custom", "Primeiro adicione a quantidade de xícaras que deseja");
                buttonRequestPressed = false;
            }
            //ESP_LOGD("custom", "idle: %d request: %d", idle, buttonRequestPressed);

            if(buttonRequestPressed && requestedCups > 0 && idle) {
                this->hasCup = cup.checkCup();
                if(this->hasCup) {
                    ESP_LOGD("custom", "Tem xícara");
                    buttonRequestPressed = false;
                    digitalWrite(portaReleBomba, HIGH);
                    digitalWrite(portaReleCoffe, HIGH);
                    digitalWrite(ledBuiltIn, HIGH);

                    idle = false;
                    fill = true;
                }
            }

            if(fill)
                fill = fill_up();
            // if machine stop filling, set some variables and change states
            if(!fill && !idle && !drain) {
                requestedCups = 0;
                buttonRequestPressed = false;
                digitalWrite(ledBuiltIn, LOW);
                digitalWrite(portaReleBomba, LOW);
                drain = true;
            }

            if(drain)
                drain = drain_out();
            // if machine stop drainning, set some variables and change states
            if(!fill && !idle && !drain) {
                digitalWrite(portaReleCoffe, LOW);
                lcd.clear();
                idle = true;
            }

            if (buttonAddCup.wasPressed() && idle) {
                ESP_LOGD("custom", "Apertou o botão de addCup");
                if(requestedCups < maxCupAmount)
                    requestedCups++;
                ESP_LOGD("custom", "Quantidade de xícaras pedidas: %d", requestedCups);
                lcd.clear();
            }
            if (buttonRemoveCup.wasPressed() && idle) {
                ESP_LOGD("custom", "Apertou o botão de removeCup");
                if( requestedCups > 0)
                    requestedCups--;
                ESP_LOGD("custom", "Quantidade de xícaras pedidas: %d", requestedCups);
                lcd.clear();
            }

            // display code
            lcd.setCursor(0,0);
            lcd.printf("xicaras: %d", requestedCups);

            delay(100);
        }

        void setRequestCup(int qtt) {
            this->requestedCups = qtt;
            this->buttonRequestPressed = true;
        }
        
        int getStatus() {
            if(this->idle) return 1;
            else if(this->fill) return 2;
            else return 3;
        }

        ~Coffee(){}
};

#endif //COFFEE_H
