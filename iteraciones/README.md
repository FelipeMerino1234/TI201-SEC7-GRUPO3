# Historial de Iteraciones

## Propósito

Esta carpeta documenta la evolución del prototipo **Monitor de Calidad del Agua** a través de las diferentes versiones desarrolladas durante el curso.


---

## Estructura de Carpetas

Cada iteración tiene su propia carpeta con documentación de esa versión:

```text
iteraciones/
├── iteracion_1/   # Concepto inicial - Simulación Wokwi y boceto (Avance #1 - 29/08/2026)
├── iteracion_2/   # Primera iteración - Prototipo físico en protoboard y modelo CAD base (Avance #2 - 25/10/2026)
└── iteracion_3/   # Versión final - Gemelo 3D, EasyEDA, IoT ThingSpeak y validación final (Avance #3 - 22/11/2026)
```
---

## Tabla Comparativa de Iteraciones

| Aspecto | v1 (Avance #1) | v2 (Avance #2) | v3 (Avance #3) |
| :--- | :--- | :--- | :--- |
| **Fecha** | 29/08/2026 | 25/10/2026 | 22/11/2026 |
| **Sensores** | Simulados con potenciómetros en Wokwi | DS18B20 (Temp), TDS V1.0, TSW-20M (Turbidez) | DS18B20, TDS V1.0, TSW-20M (calibrados y documentados en EasyEDA) |
| **Actuadores** | LED Verde y LED Rojo | LED Verde (`D8`) y LED Rojo (`D9`) | LED Verde (`D8`) y LED Rojo (`D9`) + Alertas virtuales en dashboard |
| **Conectividad** | Simulación virtual en navegador | Autónoma (Batería 18650) + Monitor Serial USB (9600 baudios) | Autónoma en terreno + Gateway Python vía Serial hacia nube ThingSpeak |
| **Encapsulado** | Solo boceto conceptual en papel | Modelo 3D inicial en Fusion (70 × 120 × 270 mm) | Gemelo 3D optimizado en PLA (52 × 100 × 253 mm), planos técnicos y renders |
| **Testing** | Simulación digital en Wokwi + Encuesta pre-test (46 usuarios) | Pruebas de laboratorio (agua de la llave vs. agua helada con sal) | Protocolo formal con muestras contrastantes (Apta vs. No Apta) y registro cloud |
| **Funcionalidad** | 60% (Lógica base sin conversión física) | 80% (Circuito físico calibrado y modelo CAD base) | 100% (Sistema integrado con IoT, esquemático formal y diseño reparable) |

---

## Evolución del Diseño

### Versión 1 (Iteración 1) - Concepto Inicial
**Fecha:** 29/08/2026  
**Estado:** Prototipo alpha - Prueba de concepto y simulación

**Características:**
* Circuito simulado íntegramente en la plataforma **Wokwi** utilizando potenciómetros básicos para emular entradas analógicas y validar la lógica condicional de los LEDs verde y rojo.
* Boceto conceptual de carcasa dividida en dos cámaras (electrónica superior sellada y faldón inferior para sensores) y validación de la problemática mediante encuesta pre-test a 46 excursionistas.
* **Problemas principales identificados:** Los potenciómetros de Wokwi no representan las curvas de voltaje reales de los sensores sumergibles de TDS y turbidez.
* **Aprendizajes clave:** Necesidad de implementar ecuaciones matemáticas de conversión a PPM y NTU, además de un filtro de estabilización de lecturas.

### Versión 2 (Iteración 2) - Primera Mejora
**Fecha:** 25/10/2026  
**Estado:** Prototipo funcional ensamblado en físico + Modelo CAD inicial

**Mejoras implementadas:**
* Ensamblaje del circuito físico real con placa Arduino Uno, sensor sumergible DS18B20, sensor TDS V1.0, sensor óptico de turbidez TSW-20M, interruptor SPDT y batería recargable 18650.
* Incorporación de fórmulas de conversión matemática para PPM y NTU calibradas con agua potable de la llave y filtro de promedio móvil de 10 lecturas consecutivas.
* Primer modelado 3D en Autodesk Fusion (70 × 120 × 270 mm) con cámara superior hermética, faldón inferior protector y orificio lateral de ventilación para evitar burbujas atrapadas.

### Versión 3 (Iteración 3) - Versión Final
**Fecha:** 22/11/2026  
**Estado:** Prototipo de alta resolución con ecosistema IoT y documentación formal

**Mejoras finales:**
* Optimización volumétrica del encapsulado en Fusion 360 reduciendo dimensiones a **52 × 100 × 253 mm** (197 g de PLA), incorporando un **gemelo 3D completo** con todos los componentes internos, tapa superior removible con pestaña (diseño para la reparación sin adhesivos permanentes), planos técnicos normalizados y renders fotorrealistas.
* Elaboración del esquemático eléctrico formal en **EasyEDA** (incorporando resistencia pull-up de `4,7 kΩ`, resistencias de `220 Ω` y módulo cargador TP4056) y tabla BOM detallada ($40.876 CLP).
* Implementación de arquitectura IoT mediante un **script en Python** que captura los datos seriales y los sube automáticamente cada 15 segundos al dashboard público en **ThingSpeak**.

**Resultado:**
* Sistema autónomo en terreno con respuesta binaria instantánea (LEDs) y respaldo histórico en la nube para análisis de datos.
* Validado bajo protocolo experimental con muestras contrastantes (Control Apto vs. Control No Apto).

---

## Justificación de Cambios

### Hardware

**De v1 a v2:**
* **Cambio:** Reemplazo de entradas simuladas por sensores físicos sumergibles (DS18B20, TDS V1.0, TSW-20M) y alimentación autónoma mediante batería 18650.
* **Razón:** Validar el comportamiento eléctrico real frente a variaciones de temperatura, sales y turbidez sin depender de alimentación externa.
* **Impacto:** Medición real y estable en tiempo real (validada con agua de la llave a ~23.1 °C / 271 ppm / 0 NTU y agua helada con sal a ~3 °C / >750 ppm).

**De v2 a v3:**
* **Cambio:** Formalización del circuito en EasyEDA (especificando pull-up de `4,7 kΩ`, limitadoras de `220 Ω` y módulo cargador TP4056) y priorización de conexiones desmontables (protoboard + jumpers) con tapa superior removible sin pegamentos fijos.
* **Razón:** Garantizar la reproducibilidad eléctrica del prototipo y facilitar el mantenimiento, recarga de batería y reemplazo rápido de sensores en terreno (Diseño para la Reparación).
* **Impacto:** Reducción del tiempo de mantenimiento en campo y eliminación de fallos por conexiones improvisadas.

### Software

**De v1 a v2:**
* Incorporación de librerías `OneWire.h` y `DallasTemperature.h`, ecuaciones de conversión a `ppm` y `NTU` calibradas con agua de la llave, y promediado móvil de 10 muestras consecutivas bajo umbrales AquaTabs/EPA/OMS (> 10 °C, < 5 NTU, < 500 ppm).

**De v2 a v3:**
* Desarrollo de un script gateway en **Python** (`pyserial` y `requests`) que lee la trama serial del Arduino Uno, evalúa la aptitud del agua y envía los datos en tiempo real a la API de **ThingSpeak** (actualización cada 15 segundos) para visualización en gauges, gráficas históricas y alertas virtuales.

### Diseño 3D

**De v1 a v2:**
* Transición desde un boceto bidimensional a un modelo paramétrico 3D de paralelepípedo (70 × 120 × 270 mm) dividido en cámara superior seca y faldón inferior abierto con orificio lateral de desaireación.

**De v2 a v3:**
* Compactación de dimensiones exteriores a **52 × 100 × 253 mm**, creación de gemelo digital con volúmenes reales de todos los componentes para verificar interferencias, diseño de tapa superior removible con pestaña de agarre, planos técnicos ortogonales normalizados y renders fotorrealistas.

---

## Incorporación de Feedback

### Feedback del Avance #1 — Cambios en v2
1. **Revisión técnica con el Profesor Sebastián Duarte (encargado del DEC):** Se advirtió que la electrónica quedaba expuesta a riesgo de daño por contacto con agua durante la medición en terreno.
   * **Acción tomada:** Se rediseñó la arquitectura física del encapsulado para aislar e impermeabilizar completamente la cámara superior (Arduino, protoboard y batería) respecto de la zona inferior de inmersión de sensores.

### Feedback del Avance #2 — Cambios en v3
1. **Refinamiento hacia entrega final (Avance #3):** Necesidad de formalizar la documentación de ingeniería, optimizar el volumen del encapsulado y dotar al sistema de registro histórico de datos sin encarecer el hardware con una pantalla LCD.
   * **Acción tomada:** Se compactó la carcasa a 52 × 100 × 253 mm con diseño reparable (tapa removible con pestaña), se generó el esquemático oficial en EasyEDA, se elaboró el BOM con costos en CLP y se integró el puente serial en Python hacia ThingSpeak.

### Feedback de Usuarios — Cambios en v2 y v3
1. **Resultados de encuesta pre-test (46 excursionistas):** El 65,2% declaró desconocer qué factores afectan a las pastillas potabilizadoras y reportó baja confianza (2,11/5) al evaluar el agua visualmente, valorando con 4,07/5 un dispositivo de confirmación simple.
   * **Acción tomada:** Se mantuvo una interfaz binaria ultraclarificada en terreno (LED Verde / LED Rojo) calibrada a los estándares de AquaTabs, complementada con un dashboard web en ThingSpeak para análisis detallado post-ruta.

---

## Métricas de Mejora

| Métrica | v1 | v2 | v3 | Mejora Total |
| :--- | :--- | :--- | :--- | :--- |
| **Variables medidas físicamente** | 0 (Simuladas) | 3 (Temp, TDS, NTU) | 3 (Temp, TDS, NTU) | +100% medición real |
| **Volumen del encapsulado** | Sin CAD | 70 × 120 × 270 mm (2.268 cm³) | 52 × 100 × 253 mm (1.315 cm³) | -42% reducción de volumen (más portátil) |
| **Estabilización de señal** | 1 lectura directa | Promedio de 10 lecturas | Promedio de 10 lecturas | Eliminación de ruido analógico |
| **Persistencia de datos** | Sin registro | Solo visualización volátil en Serial | Almacenamiento cloud en ThingSpeak (cada 15 s) | Historial permanente con fecha/hora |
| **Reparabilidad y mantenimiento** | Sin carcasa | Sellado básico | Tapa removible con pestaña + conectores desmontables | Intervención sin dañar carcasa |

---

## Lecciones Aprendidas

### Técnicas
* Pasar de simulación en Wokwi a sensores reales exige calibrar experimentalmente los voltajes analógicos (`V_TDS` y `V_TURB`), incorporar resistencias adecuadas (`4,7 kΩ` pull-up y `220 Ω` limitadoras) y promediar múltiples lecturas (10 por ciclo) para evitar falsos positivos.
* Integrar un gateway ligero en Python hacia ThingSpeak permite obtener telemetría, gráficas históricas y respaldo en la nube sin sacrificar la autonomía energética ni el bajo costo del dispositivo en terreno.

### De Proceso
* Validar temprano los umbrales operativos con normativa real (AquaTabs, EPA y OMS) permitió acotar el alcance del prototipo, y desarrollar un gemelo 3D con los volúmenes reales de los componentes evitó interferencias mecánicas al reducir el tamaño en un 42%.

### De Trabajo en Equipo
* Dividir el desarrollo en frentes especializados (firmware en Arduino/Python, electrónica y BOM en EasyEDA, gemelo 3D y planos en Fusion 360, y validación experimental) permitió integrar todas las evidencias de forma trazable en el repositorio GitHub.
