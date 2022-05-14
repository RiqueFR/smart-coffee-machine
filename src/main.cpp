#include <Arduino.h>
#include <button.h>
#include <cup.h>
#include <ultrasonic.h>

const int trigPinCup = 5;
const int echoPinCup = 18;
const int trigPinWat = 19;
const int echoPinWat = 21;

const int buttonRequestPin = 25;
const int buttonAddCupPin = 26;

int ledBuiltIn = 2;

int actualQtdCup = 0;
int requestedCups = 5;

const int mmToCups = 30;
const int maxMm = 200;

// const int portaRele = 5;

// Ultrasonic ultrasonic = Ultrasonic(trigPinWat, echoPinWat);
// Cup cup = Cup(trigPinCup, echoPinCup);
// Button buttonRequest = Button(buttonRequestPin);
Button buttonAddCup = Button(buttonAddCupPin);

void setup() {
    // pinMode(portaRele, OUTPUT);
    pinMode(ledBuiltIn, OUTPUT);
    Serial.begin(115200);  // Starts the serial communication
}

void loop() {
    // Calculate the distance
    // float distanceMm = ultrasonic.getDistanceMm();
    // bool hasCup = cup.checkCup();

    // if(hasCup){
    //   Serial.println("Tem xícara");
    //   while(actualQtdCup < requestedCups && hasCup){
    //     digitalWrite(ledBuiltIn, HIGH);
    //     Serial.print("Distance (mm): ");
    //     Serial.println(distanceMm);

    //     actualQtdCup = (maxMm - distanceMm) / mmToCups;
    //     Serial.print("Quantidade atual de xícaras: ");
    //     Serial.println(actualQtdCup);

    //     distanceMm = ultrasonic.getDistanceMm();
    //     hasCup = cup.checkCup();

    //     delay(500);
    //   }
    // }else{
    //   Serial.println("Não tem xícara");
    //   digitalWrite(ledBuiltIn, LOW);
    // }

    //   digitalWrite(portaRele, HIGH);
    //   delay(1500);
    //   digitalWrite(portaRele, LOW);
    // if (buttonRequest.wasPressed()) {
    //     Serial.println("Apertou o botão de request");
    // }

    if (buttonAddCup.wasPressed()) {
        Serial.println("Apertou o botão de addCup");
        requestedCups++;
        Serial.print("Quantidade de xícaras pedidas: ");
        Serial.println(requestedCups);
    }

    // Serial.println("Nenhum botão foi apertado");

    // delay(1000);
}