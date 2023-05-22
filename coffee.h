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
        int maxCupAmount = 15;

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

        const float  mmToCups = 6.5;
        const float  maxMm = 157;
        float lastRead = 157;

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

        MyButton buttonRequest = MyButton(13);
        MyButton buttonAddCup = MyButton(12);
        MyButton buttonRemoveCup = MyButton(14);

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
        bool fill_up(float distanceMm) {
            ESP_LOGD("custom", "Enchendo reservatorio ++++++++++++++");
            ESP_LOGD("custom", "Distance (mm): %f", distanceMm);
            // check if the machine fill with the correct amount of cups
            if(actualQtdCup < requestedCups) {
                if(distanceMm < 30)
                    return true;

                lcd.setCursor(0,1);
                lcd.printf("Status: Enchendo");

                if(distanceMm > maxMm) {
                    return true;
                }

                actualQtdCup = (maxMm - distanceMm) / mmToCups;
                ESP_LOGD("custom", "Quantidade atual de xícaras: %d", actualQtdCup);

                return true;
            }
            return false;
        }

        // return true if the coffee maxine still needs to drain out
        bool drain_out(float distanceMm) {
            // check if the machine emptied
            lcd.setCursor(0,1);
            lcd.printf("Status: Coando  ");
            ESP_LOGD("custom", "Esvaziando reservatorio -------------");
            ESP_LOGD("custom", "Distance (mm): %f", distanceMm);
            if(distanceMm < maxMm || distanceMm > 165) {
                return true;
            }
            return false;
        }

        float distance_difference(float distanceMm) {
            float dif = distanceMm - lastRead;
            if(dif < 0) dif *= -1;
            return dif;
        }

        void loop() {
            float distanceMm;
            //ESP_LOGD("custom", "sensor: %.2f ==============", ultrasonic.getDistanceMm());
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
                    //digitalWrite(ledBuiltIn, HIGH);

                    idle = false;
                    fill = true;
                }
            }

            if(fill) {
                distanceMm = ultrasonic.getDistanceMm();
                if(distance_difference(distanceMm) < 20) {
                    fill = fill_up(distanceMm);
                }
                lastRead = distanceMm;
            }
            // if machine stop filling, set some variables and change states
            if(!fill && !idle && !drain) {
                requestedCups = 0;
                buttonRequestPressed = false;
                //digitalWrite(ledBuiltIn, LOW);
                digitalWrite(portaReleCoffe, HIGH);
                digitalWrite(portaReleBomba, LOW);
                actualQtdCup = 0;
                drain = true;
            }

            if(drain) {
                distanceMm = ultrasonic.getDistanceMm();
                if(distance_difference(distanceMm) < 20) {
                    drain = drain_out(distanceMm);
                }
                lastRead = distanceMm;
            }
            // if machine stop drainning, set some variables and change states
            if(!fill && !idle && !drain) {
                digitalWrite(portaReleCoffe, LOW);
                digitalWrite(portaReleBomba, LOW);
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
