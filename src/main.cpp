#include <Arduino.h>
#include <coffee.h>
 
Coffee machine = Coffee(30);

void setup() {
    machine.setup();
}

void loop() {
    machine.loop();
}