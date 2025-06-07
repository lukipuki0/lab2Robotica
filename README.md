# lab2Robotica

# Lab1Robotica

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
