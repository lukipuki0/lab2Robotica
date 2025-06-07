#include <Wire.h>
#include "Adafruit_TCS34725.h"

const int trigPin = 2;
const int echoPin = 3;
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);


const int enA = 9;  
const int in1 = 8;
const int in2 = 7;

// Motor Derecho
const int enB = 6; 
const int in3 = 5;
const int in4 = 4;

const int DISTANCIA_OBSTACULO = 10;
const int UMBRAL_DETECCION_COLOR = 250; 

void setup() {
  Serial.begin(9600);

 
  if (!tcs.begin()) {
    Serial.println("No se encontró el sensor TCS34725... revisa las conexiones SCL (A5) y SDA (A4).");
    while (1);
  }
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  detener();
  Serial.println("Setup completo. Robot listo para la Parte 2.");
}

void loop() {
  long duration;
  int distancia;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distancia = duration * 0.034 / 2;

  if (distancia < DISTANCIA_OBSTACULO && distancia > 0) {
    Serial.print("Obstaculo detectado a ");
    Serial.print(distancia);
    Serial.println(" cm. ¡Evadiendo!");
    detener();
    delay(200);
    retroceder(150);
    delay(400);
    girarDerecha(150);
    delay(300);
    detener();
  } else {
    uint16_t r, g, b, c;
    tcs.getRawData(&r, &g, &b, &c);

    if (r > g && r > b && r > UMBRAL_DETECCION_COLOR) {
      Serial.println("Rojo detectado. Girando a la izquierda.");
      girarIzquierda(150);
      delay(100);
    } else if (b > r && b > g && b > UMBRAL_DETECCION_COLOR) {
      Serial.println("Azul detectado. Girando a la derecha.");
      girarDerecha(150);
      delay(100);
    } else if (g > r && g > b && g > UMBRAL_DETECCION_COLOR) {
      Serial.println("Verde detectado. Deteniendo.");
      detener();
      delay(500);
    } else {
      Serial.println("Camino libre. Avanzando.");
      avanzar(150);
    }
  }
  delay(50);
}

void avanzar(int velocidad) {
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW); analogWrite(enA, velocidad);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW); analogWrite(enB, velocidad);
}

void retroceder(int velocidad) {
  digitalWrite(in1, LOW); digitalWrite(in2, HIGH); analogWrite(enA, velocidad);
  digitalWrite(in3, LOW); digitalWrite(in4, HIGH); analogWrite(enB, velocidad);
}

void girarDerecha(int velocidad) {
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW); analogWrite(enA, velocidad);
  digitalWrite(in3, LOW); digitalWrite(in4, HIGH); analogWrite(enB, velocidad);
}

void girarIzquierda(int velocidad) {
  digitalWrite(in1, LOW); digitalWrite(in2, HIGH); analogWrite(enA, velocidad);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW); analogWrite(enB, velocidad);
}

void detener() {
  analogWrite(enA, 0); analogWrite(enB, 0);
}