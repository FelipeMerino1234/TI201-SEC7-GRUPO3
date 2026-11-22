# Declaración de Fuentes e Integridad Académica

En cumplimiento con la política de integridad académica del curso **TEI 201 (Sección 7, Grupo 3)** de la Universidad Adolfo Ibáñez, este documento detalla las librerías externas, referencias técnicas, código adaptado y herramientas de Inteligencia Artificial utilizadas en el desarrollo del proyecto **Monitor de Calidad del Agua (M.C.A.)**.

---

## 1. Librerías Externas Utilizadas

### Firmware (Arduino IDE)
* **`OneWire.h`**: Protocolo de comunicación 1-Wire para la lectura del sensor digital de temperatura DS18B20.
* **`DallasTemperature.h`**: Librería de control y conversión de temperatura para el sensor DS18B20.
* **`EEPROM.h`**: Librería estándar de Arduino utilizada para el almacenamiento local no volátil de las muestras en terreno.

### Gateway IoT (Python)
* **`pyserial`**: Lectura de datos desde el puerto serial (USB) enviados por la placa Arduino Uno.
* **`requests`**: Envío de peticiones HTTP hacia la API de ThingSpeak para el almacenamiento en la nube.

---

## 2. Código Adaptado y Referencias Técnicas de Sensores
Las fórmulas matemáticas de conversión de voltaje a partes por millón (ppm) y unidades nefelométricas de turbidez (NTU), así como los procedimientos base de calibración analógica, fueron adaptados a partir de la documentación oficial de los fabricantes:
* **Sensor de Turbidez (TSW-20M):** DFRobot Wiki — *Analog Turbidity Sensor for Arduino (SKU: SEN0189)*. https://wiki.dfrobot.com/Turbidity_sensor_SKU_SEN0189
* **Sensor de Sólidos Disueltos (TDS V1.0):** DFRobot Wiki — *Gravity: Analog TDS Sensor/Meter for Arduino (SKU: SEN0244)*. https://wiki.dfrobot.com/Gravity__Analog_TDS_Sensor___Meter_For_Arduino_SKU__SEN0244

### Referencias de Umbrales de Potabilización
* **Aquatabs (Medentech):** Lineamientos de turbidez (< 5 NTU) y tiempo de contacto según temperatura (> 10 °C). https://www.aquatabs.com/products/aquatabs-granules/
* **EPA (Agencia de Protección Ambiental de EE. UU.) y OMS:** Nivel Máximo de Contaminante Secundario (SMCL) para Sólidos Totales Disueltos (< 500 ppm). https://www.epa.gov/sdwa/secondary-drinking-water-standards-guidance-nuisance-chemicals

---

## 3. Plataformas y Software de Apoyo
* **Autodesk Fusion 360:** Modelado paramétrico del gemelo 3D, planos técnicos normalizados y renders fotorrealistas.
* **EasyEDA:** Diseño y exportación del esquemático electrónico oficial.
* **ThingSpeak (MathWorks):** Almacenamiento histórico en la nube, gráficos evolutivos y *gauges* de umbral.
* **Wokwi:** Simulación inicial del circuito y lógica de programación de Arduino.

---

## 4. Declaración de Uso de Inteligencia Artificial

* **Avance 1:** Se utilizó Inteligencia Artificial como herramienta de investigación para identificar materiales y componentes electrónicos adecuados, evaluar la viabilidad técnica del prototipo y apoyar la estructuración inicial del proyecto.
* **Avance 2:** Se empleó como guía en el ensamblaje físico, apoyo en la estructuración del código fuente de Arduino, depuración de errores de ejecución y calibración de sensores, además de revisión analítica del informe frente a la pauta.
* **Avance 3:** Se utilizó como herramienta de aprendizaje paso a paso para configurar la arquitectura IoT y el script de envío en Python hacia ThingSpeak, elaborar el esquemático en EasyEDA, generar planos técnicos y renders en Fusion 360, y estructurar el repositorio en GitHub. También se empleó para recibir recomendaciones de diseño para la reparación, estructuración del protocolo de pruebas y verificación de criterios de evaluación.

*Todas las recomendaciones, fórmulas y fragmentos de código generados o adaptados fueron revisados, probados y validados por los integrantes del equipo.*
