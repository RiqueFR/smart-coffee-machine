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

        MyButton buttonRequest = MyButton(25);
        MyButton buttonAddCup = MyButton(26);
        MyButton buttonRemoveCup = MyButton(27);

        bool hasCup = false;
    
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


        void loop() {
            float distanceMm = maxMm;

            if (buttonRequest.wasPressed() && !buttonRequestPressed) {
                ESP_LOGD("custom", "Apertou o botão de request");
                buttonRequestPressed = true;
            }

            if(buttonRequestPressed && requestedCups == 0) {
                ESP_LOGD("custom", "Primeiro adicione a quantidade de xícaras que deseja");
                buttonRequestPressed = false;
            }

            if(buttonRequestPressed && requestedCups > 0) {
                this->hasCup = cup.checkCup();
                if(this->hasCup) {
                    ESP_LOGD("custom", "Tem xícara");
                    buttonRequestPressed = false;
                    digitalWrite(portaReleBomba, HIGH);
                    digitalWrite(portaReleCoffe, HIGH);
                    digitalWrite(ledBuiltIn, HIGH);

                    // enchendo o reservatorio
                    while(actualQtdCup < requestedCups) {
                        distanceMm = ultrasonic.getDistanceMm();
                        // hasCup = cup.checkCup();

                        lcd.setCursor(0,1);
                        lcd.printf("Status: Enchendo");

                        if(distanceMm > maxMm) {
                            continue;
                        }

                        ESP_LOGD("custom", "Enchendo reservatorio ++++++++++++++");
                        ESP_LOGD("custom", "Distance (mm): %f", distanceMm);
                        // Serial.print("Tem xícara: ");
                        // ESP_LOGD("custom", hasCup);


                        actualQtdCup = (maxMm - distanceMm) / mmToCups;
                        ESP_LOGD("custom", "Quantidade atual de xícaras: %d", actualQtdCup);

                        delay(200);
                    }
                    requestedCups = 0;
                    buttonRequestPressed = false;
                    digitalWrite(ledBuiltIn, LOW);
                    digitalWrite(portaReleBomba, LOW);
                    distanceMm = ultrasonic.getDistanceMm();
                    while(actualQtdCup > 0) {// && hasCup) { // espera reservatorio esvaziar
                        distanceMm = ultrasonic.getDistanceMm();

                        lcd.setCursor(0,1);
                        lcd.printf("Status: Coando  ");

                        // hasCup = cup.checkCup();
                        if(distanceMm > maxMm) {
                            continue;
                        }

                        ESP_LOGD("custom", "Esvaziando reservatorio -------------");
                        ESP_LOGD("custom", "Distance (mm): %f", distanceMm);
                        actualQtdCup = (maxMm - distanceMm) / mmToCups;
                        ESP_LOGD("custom", "Quantidade atual de xícaras: %d", actualQtdCup);

                        delay(200);
                    }

                    digitalWrite(portaReleCoffe, LOW);
                    lcd.clear();
                }
            }

            if (buttonAddCup.wasPressed()) {
                ESP_LOGD("custom", "Apertou o botão de addCup");
                if(requestedCups < maxCupAmount)
                    requestedCups++;
                ESP_LOGD("custom", "Quantidade de xícaras pedidas: %d", requestedCups);
                lcd.clear();
            }
            if (buttonRemoveCup.wasPressed()) {
                ESP_LOGD("custom", "Apertou o botão de removeCup");
                if( requestedCups > 0)
                    requestedCups--;
                ESP_LOGD("custom", "Quantidade de xícaras pedidas: %d", requestedCups);
                lcd.clear();
            }

            // display code
            lcd.setCursor(0,0);
            lcd.printf("xicaras: %d", requestedCups);

            delay(50);
        }

        ~Coffee(){}
};

#endif //COFFEE_H
