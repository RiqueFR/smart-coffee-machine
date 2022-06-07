#include "coffee.h"

Coffee::Coffee(int maxCupAmount) {
    this->maxCupAmount = maxCupAmount;
}

void Coffee::setup() {
    pinMode(portaReleBomba, OUTPUT);
    pinMode(portaReleCoffe, OUTPUT);
    pinMode(ledBuiltIn, OUTPUT);

    lcd.init();
    lcd.backlight();
    
    Serial.begin(115200);  // Starts the serial communication
}

void Coffee::loop() {
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
            
            lcd.setCursor(0,1);
            lcd.printf("Status: Enchendo");

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
            
            lcd.setCursor(0,1);
            lcd.printf("Status: Coando  ");

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
        lcd.clear();
    } else{
        // Serial.println("Não tem xícara");
    }

    if (buttonAddCup.wasPressed()) {
        Serial.println("Apertou o botão de addCup");
        if(requestedCups < maxCupAmount)
            requestedCups++;
        Serial.print("Quantidade de xícaras pedidas: ");
        Serial.println(requestedCups);
        lcd.clear();
    }
    if (buttonRemoveCup.wasPressed()) {
        Serial.println("Apertou o botão de removeCup");
        if( requestedCups > 0)
            requestedCups--;
        Serial.print("Quantidade de xícaras pedidas: ");
        Serial.println(requestedCups);
        lcd.clear();
    }

    // display code
    lcd.setCursor(0,0);
    lcd.printf("xicaras: %d", requestedCups);

    // delay(100);
}