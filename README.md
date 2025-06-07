# lab2Robotica

## Parte 1

Integrantes:
- Lucas Erazo
- José Lara
- Claudio Toledo
- Pablo Silva
- José Villamayor

## Preguntas I

• ¿ Qué es la percepción en robótica y por qué es fundamental en los
sistemas autónomos?
La percepción en robótica es la capacidad que tiene un robot para recolectar datos del mundo exterior (y a veces de su propio estado interno) y transformarlos en información útil para navegar, interactuar o cumplir tareas.

Es fundamental en los sistemas autónomos porque para que los robots tomen decisiones inteligentes, necesitan percibir qué hay a su alrededor y así construir una representación del mundo. Esta comprensión del entorno, lograda a través de los sensores, les permite actuar de manera autónoma

• En el sensor ultrasónico HC-SR04 ¿ Qué parámetro se mide para calcular la distancia?

En el sensor ultrasónico HC-SR04, el parámetro que se mide para calcular la distancia es el tiempo que tarda una onda ultrasónica en viajar desde el sensor hasta un objeto y regresar como un eco. Específicamente, el microcontrolador mide la duración del pulso en el pin ECHO, que corresponde al tiempo total de viaje de la onda sonora. Luego, este tiempo se convierte en distancia usando la velocidad del sonido.

• ¿ Cómo influye el ruido en las mediciones del sensor ultrasónico y cómo
podría reducirse?

El ruido puede influir significativamente en las mediciones del sensor ultrasónico, provocando datos inconsistentes, es decir, mediciones que saltan bruscamente sin una causa real. Factores ambientales como el viento o las características del objeto como superficies blandas también pueden afectar negativamente la precisión de las lecturas, comportándose como fuentes de ruido o error.


Para reducir el impacto del ruido en las mediciones de un sensor ultrasónico, se pueden aplicar técnicas de filtrado de datos. Estas técnicas buscan eliminar o reducir el ruido e imperfecciones presentes en las señales. Algunos filtros comunes que ayudan a suavizar la señal y eliminar picos falsos son:

• Filtro de media móvil: Promedia los últimos N valores para suavizar la señal.
• Filtro de media ponderada: Similar a la media móvil, pero da más peso a los valores más recientes.
• Filtro pasa bajos: Atenúa las frecuencias altas, que a menudo corresponden al ruido rápido, suavizando la señal.

## Codigo

````
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
````

## Análisis de variaciones en las lecturas 

Para evaluar la respuesta de los sensores se grabaron varios videos con escenarios controlados:

- **Sensor de color (3 videos):**  
  Se presentaron tres colores (verde, rojo y azul) frente al TCS34725; en cada caso el sensor detectó el color correspondiente y entregó un valor más elevado para el canal relevante.
1) [Test ROJO](https://drive.google.com/file/d/1tf9KPwQ9vSKIjQVYJF45yj0FyOX0UVd6/view?usp=drive_link)
2) [Test VERDE](https://drive.google.com/file/d/1tX2ZdEYJqnu2uGdY3ctQrrCOVd2bN0VI/view?usp=drive_link)
3) [Test AZUL](https://drive.google.com/file/d/1tf9X52SKuO85PsJLWKorj5bZKR6HQSET/view?usp=drive_link)
- **Sensor ultrasónico HC-SR04 :**  
  A medida que la mano se acerca y se aleja del sensor, el valor de distancia registrado cambia acorde a la posición.
1) [DistanciaEcoSensor](https://drive.google.com/file/d/1teH5Sy6mwrs5qpJ_SjsL9Sa3c9MW02mg/view?usp=drive_link)

## Parte 2

## Preguntas II

• Si el robot detecta el color rojo en el suelo ¿ Qué acción debería tomar?
¿ Por qué?
• Si el sensor ultrasónico detecta valores erráticos ¿ Qué estrategias
podrías aplicar para mejorar la precisión?

Filtrado estadístico: aplicar un filtro de mediana o un promedio móvil para descartar valores “espurios” que quedan fuera del rango físico plausible.

Calibración y rechazo de outliers: usar mediciones en un entorno controlado para ajustar offset y escala, y descartar automáticamente lecturas muy lejanas de la media .

Filtro de Kalman: combina la predicción (modelo de movimiento del robot) con la medición ultrasónica, ponderando según la incertidumbre de cada fuente, para obtener estimaciones más estables y precisas.

• Si tuvieras que integrar un nuevo sensor para mejorar la navegación
del robot ¿ Cuál eligiráas y por qué?.

Un LIDAR 2D  porque ofrece:

Muy alta precisión en la medición de distancias.

Alcance largo (decenas de metros), ideal para mapear y detectar obstáculos temprano.

Velocidad de muestreo muy rápida, compatible con técnicas de SLAM para construir mapas en tiempo real.
Frente a un sensor RGB-D (que además aporta color) o al ultrasonido, el LIDAR es más robusto ante variaciones de iluminación y superficies no reflectantes

• ¿Cuál es el tiempo de respuesta del robot al detectar un cambio de
color?

Está limitado por la frecuencia de muestreo del sensor y el ciclo de procesamiento. Si, por ejemplo, utilizamos un sensor RGB con un bucle de control a 100 Hz (Δt = 0,01 s), cada muestra —incluyendo la lectura RGB y la comparación con el umbral de “rojo puro”— se completa en ≈10 ms. Añadiendo unos pocos milisegundos más de procesado en el microcontrolador, la respuesta total queda por debajo de 20 ms.

## Codigo 

````

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
````
• Algoritmo de planificacion de rutas reacivos: evitacion de obstaculos,
y deteccion de colores basado en reglas 
• Implementacion correcta de umbrales de deteccion
• Pruebas y ajustes en entorno real 
• Reflexion sobre posibles mejoras en la detección


