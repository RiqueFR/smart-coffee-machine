#include <Arduino.h>
#include "../lib/ultrasonic/ultrasonic.h"

const int trigPin = 5;
const int echoPin = 18;

Ultrasonic ultrasonic = Ultrasonic(trigPin, echoPin);

void setup() {
  Serial.begin(115200); // Starts the serial communication
}

void loop() {
  // Calculate the distance
  float distanceMm = ultrasonic.getDistanceMm();
  
  // Prints the distance in the Serial Monitor
  Serial.print("Distance (mm): ");
  Serial.println(distanceMm);
  
  delay(1000);
}