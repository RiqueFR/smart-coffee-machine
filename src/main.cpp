#include <Arduino.h>
#include <ultrasonic.h>
#include <cup.h>

const int trigPin = 5;
const int echoPin = 18;

//const int portaRele = 5;

//Ultrasonic ultrasonic = Ultrasonic(trigPin, echoPin);
Cup cup = Cup(trigPin, echoPin);

void setup() {
  //pinMode(portaRele, OUTPUT);
  Serial.begin(115200); // Starts the serial communication
}

void loop() {
  // Calculate the distance
  // float distanceMm = ultrasonic.getDistanceMm();
  
  // Prints the distance in the Serial Monitor
  // Serial.print("Distance (mm): ");
  // Serial.println(distanceMm);
  Serial.println(cup.checkCup());

//   digitalWrite(portaRele, HIGH);
//   delay(1500);
//   digitalWrite(portaRele, LOW);
  delay(1000);
}