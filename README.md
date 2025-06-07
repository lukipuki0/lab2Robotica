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

##Codigo

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

### 1.3 Análisis de variaciones en las lecturas 

Para evaluar la respuesta de los sensores se grabaron varios videos con escenarios controlados:

- **Sensor de color (3 videos):**  
  Se presentaron tres colores (verde, rojo y azul) frente al TCS34725; en cada caso el sensor detectó el color correspondiente y entregó un valor más elevado para el canal relevante.
1) [Test ROJO](https://drive.google.com/file/d/1tf9KPwQ9vSKIjQVYJF45yj0FyOX0UVd6/view?usp=drive_link)
2) [Test VERDE](https://drive.google.com/file/d/1tX2ZdEYJqnu2uGdY3ctQrrCOVd2bN0VI/view?usp=drive_link)
3) [Test AZUL](https://drive.google.com/file/d/1tf9X52SKuO85PsJLWKorj5bZKR6HQSET/view?usp=drive_link)
- **Sensor ultrasónico HC-SR04 :**  
  A medida que la mano se acerca y se aleja del sensor, el valor de distancia registrado cambia acorde a la posición.
1) [DistanciaEcoSensor](https://drive.google.com/file/d/1teH5Sy6mwrs5qpJ_SjsL9Sa3c9MW02mg/view?usp=drive_link)

