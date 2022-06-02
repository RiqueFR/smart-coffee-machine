#include <Arduino.h>
#include <button.h>
#include <cup.h>
#include <ultrasonic.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
 
const int maxCupAmount = 30;

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

// LiquidCrystal_I2C lcd(0x27, 16, 2);

Ultrasonic ultrasonic = Ultrasonic(trigPinWat, echoPinWat);
Cup cup = Cup(trigPinCup, echoPinCup);
Button buttonRequest = Button(buttonRequestPin);
Button buttonAddCup = Button(buttonAddCupPin);
Button buttonRemoveCup = Button(buttonRemoveCupPin);

void setup() {
    pinMode(portaReleBomba, OUTPUT);
    pinMode(portaReleCoffe, OUTPUT);
    pinMode(ledBuiltIn, OUTPUT);

    // lcd.init();
    // lcd.backlight();
    // lcd.print("ESP32 - Projeto");
    // lcd.setCursor(0, 1);
    // lcd.print("com display!");

    Serial.begin(115200);  // Starts the serial communication
}

void loop() {
    float distanceMm = maxMm;
    bool hasCup = cup.checkCup();

    if (buttonRequest.wasPressed() && !buttonRequestPressed) {
        Serial.println("Apertou o botão de request");
        buttonRequestPressed = true;
    }

    if(buttonRequestPressed && requestedCups == 0) {
        Serial.println("Primeiro adicione a quantidade de xícaras que deseja");
        buttonRequestPressed = false;
    }

    if(buttonRequestPressed && requestedCups > 0 && hasCup) {
        Serial.println("Tem xícara");
        buttonRequestPressed = false;
        digitalWrite(portaReleBomba, HIGH);
        digitalWrite(portaReleCoffe, HIGH);
        digitalWrite(ledBuiltIn, HIGH);
        // enchendo o reservatorio
        while(actualQtdCup < requestedCups){ // && hasCup){
            distanceMm = ultrasonic.getDistanceMm();
            // hasCup = cup.checkCup();
            

            if(distanceMm > maxMm){
                continue;
            }
            
            Serial.println("Enchendo reservatorio ++++++++++++++");
            Serial.print("Distance (mm): ");
            Serial.println(distanceMm);
            // Serial.print("Tem xícara: ");
            // Serial.println(hasCup);


            actualQtdCup = (maxMm - distanceMm) / mmToCups;
            Serial.print("Quantidade atual de xícaras: ");
            Serial.println(actualQtdCup);

            delay(200);
        }
        requestedCups = 0;
        buttonRequestPressed = false;
        digitalWrite(ledBuiltIn, LOW);
        digitalWrite(portaReleBomba, LOW);
        distanceMm = ultrasonic.getDistanceMm();
        while(actualQtdCup > 0){// && hasCup) { // espera reservatorio esvaziar
            distanceMm = ultrasonic.getDistanceMm();
            // hasCup = cup.checkCup();
            if(distanceMm > maxMm){
                continue;
            }

            Serial.println("Esvaziando reservatorio -------------");
            Serial.print("Distance (mm): ");
            Serial.println(distanceMm);
            actualQtdCup = (maxMm - distanceMm) / mmToCups;
            Serial.print("Quantidade atual de xícaras: ");
            Serial.println(actualQtdCup);

            delay(200);
        }

        digitalWrite(portaReleCoffe, LOW);
    } else{
        // Serial.println("Não tem xícara");
    }

    if (buttonAddCup.wasPressed()) {
        Serial.println("Apertou o botão de addCup");
        if(requestedCups < maxCupAmount)
            requestedCups++;
        Serial.print("Quantidade de xícaras pedidas: ");
        Serial.println(requestedCups);
    }
    if (buttonRemoveCup.wasPressed()) {
        Serial.println("Apertou o botão de removeCup");
        if( requestedCups > 0)
            requestedCups--;
        Serial.print("Quantidade de xícaras pedidas: ");
        Serial.println(requestedCups);
    }

    //Serial.println("Nenhum botão foi apertado");

    // delay(100);
}