#include <Wire.h>
#include "Adafruit_TCS34725.h"

const int trigPin = 2;
const int echoPin = 3;


Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(9600);

  if (tcs.begin()) {
    Serial.println("Sensor de color TCS34725 encontrado!");
  } else {
    Serial.println("No se encontró el sensor TCS34725... revisa las conexiones.");
    while (1); r
  }

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  leerDistancia();
  
  leerColor();

  delay(1000);
}

void leerDistancia() {
  long duration;
  int distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  
  distance = duration * 0.034 / 2;

  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.print(" cm. ");
}

void leerColor() {
  uint16_t red, green, blue, clear;

  tcs.setInterrupt(false);
  delay(60); 
  tcs.getRawData(&red, &green, &blue, &clear);
  tcs.setInterrupt(true);

  Serial.print("R: " + String(red));
  Serial.print(" G: " + String(green));
  Serial.print(" B: " + String(blue));
  Serial.println(" C: " + String(clear));
}