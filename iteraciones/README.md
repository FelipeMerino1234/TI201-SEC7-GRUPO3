# Historial de Iteraciones

## Propósito

Esta carpeta documenta la evolución del prototipo **Monitor de Calidad del Agua ** a través de las diferentes versiones desarrolladas durante el curso.

**CRÍTICO:** Demostrar el proceso iterativo es un requisito para obtener puntaje completo en "Integración y Refinamiento" (2.5 puntos).

---

## Estructura de Carpetas

Cada iteración tiene su propia carpeta con documentación de esa versión:

```text
iteraciones/
├── iteracion_1/   # Concepto inicial - Simulación Wokwi y boceto (Avance #1)
├── iteracion_2/   # Primera iteración - Prototipo físico en protoboard y modelo CAD 3D (Avance #2)
└── iteracion_3/   # Versión final - Carcasa impresa en 3D y pruebas en terreno (Avance #3)
```

---

## Contenido de Cada Iteración

Cada carpeta debe incluir:

1. **README.md** - Descripción de la versión
2. **Fotos** - Imágenes del prototipo en ese estado
3. **Esquema** - Circuito de esa versión (si cambió)
4. **Código** - Versión del software (si cambió)
5. **Notas** - Problemas identificados y mejoras planificadas

---

## Tabla Comparativa de Iteraciones

| Aspecto | v1 (Avance #1) | v2 (Avance #2) | v3 (Avance #3) |
| :--- | :--- | :--- | :--- |
| **Fecha** | *(Completar fecha Avance 1)* | 25/10/2026 | *(Completar fecha Avance 3)* |
| **Sensores** | Simulados con potenciómetros en Wokwi | DS18B20 (Temp), TDS V1.0, TSW-20M (Turbidez) | DS18B20, TDS V1.0, TSW-20M (integrados) |
| **Actuadores** | LED Verde y LED Rojo | LED Verde (pin 8) y LED Rojo (pin 9) | LED Verde y LED Rojo |
| **Conectividad** | Simulación virtual | Autónoma (Batería 18650) + Serial USB (9600 baudios) | Autónoma en terreno (Batería 18650) |
| **Encapsulado** | Solo boceto conceptual en papel | Modelo 3D en Autodesk Fusion (70×120×270 mm) | Impresión 3D en PLA impermeabilizada |
| **Testing** | Simulación digital en Wokwi + Encuesta pre-test (46 personas) | Pruebas de laboratorio (agua de la llave y agua helada con sal) | *(Completar pruebas en senderos RM)* |
| **Funcionalidad** | 60% (Lógica base sin conversión real) | 80% (Circuito físico calibrado, falta carcasa impresa) | 100% *(Prototipo final integrado)* |

---

## Evolución del Diseño

### Versión 1 (Iteración 1) - Concepto Inicial
**Fecha:** *(Completar fecha Avance 1)*  
**Estado:** Prototipo alpha - Prueba de concepto y simulación

**Características:**
* Circuito simulado íntegramente en la plataforma **Wokwi** utilizando potenciómetros básicos para simular las entradas analógicas y validar la lógica condicional de los LEDs verde y rojo.
* Diseño conceptual en boceto de un cuerpo dividido en dos secciones (electrónica superior y sensores inferiores).
* **Problemas principales identificados:** Los potenciómetros de Wokwi no reflejan el comportamiento físico ni las curvas de voltaje reales de los sensores sumergibles de TDS y turbidez.
* **Aprendizajes clave:** Necesidad de implementar ecuaciones matemáticas de conversión a PPM y NTU y un filtro de estabilización de señales antes de pasar a terreno.

### Versión 2 (Iteración 2) - Primera Mejora
**Fecha:** 25/10/2026  
**Estado:** Prototipo funcional ensamblado en físico + Diseño CAD 3D

**Mejoras implementadas:**
* Ensamblaje del circuito físico real con placa Arduino Uno, sensor sumergible DS18B20, sensor TDS V1.0, sensor óptico de turbidez TSW-20M, interruptor SPDT y batería recargable 18650.
* Incorporación de fórmulas de conversión matemática para PPM y NTU calibradas con agua potable de la llave y filtro de promedio móvil de 10 lecturas consecutivas.
* Modelado 3D en Autodesk Fusion (70 × 120 × 270 mm) con cámara superior hermética, faldón inferior protector y orificio lateral de ventilación para evitar burbujas atrapadas.

### Versión 3 (Iteración 3) - Versión Final
**Fecha:** *(Completar fecha Avance 3)*  
**Estado:** Prototipo final impreso en 3D y probado en terreno

**Mejoras finales:**
* Fabricación de la carcasa mediante impresión 3D en PLA e integración interna de toda la electrónica con sellado hermético en la tapa superior y paso de cables.
* *(Agregar aquí cualquier ajuste adicional realizado tras imprimir la carcasa y probar en ríos/esteros).*

**Resultado:**
* Sistema autónomo, compacto y protegido contra impactos y filtraciones.
* Validado mediante pruebas con muestras de agua en rutas de la Región Metropolitana *(confirmar si se realizaron las pruebas en senderos)*.

---

## Justificación de Cambios

### Hardware

**De v1 a v2:**
* **Cambio:** Reemplazo de entradas simuladas por sensores físicos sumergibles (DS18B20, TDS V1.0, TSW-20M) y alimentación autónoma mediante batería 18650 con módulo de carga.
* **Razón:** Validar el comportamiento eléctrico real de los sensores frente a variaciones de temperatura, sales y partículas suspendidas, además de permitir operación sin depender del PC.
* **Impacto:** Medición real y estable en tiempo real (validada con agua de la llave a ~23.1 °C / 271 ppm / 0 NTU y agua helada con sal a ~3 °C / >750 ppm).

**De v2 a v3:**
* **Cambio:** Encapsulamiento definitivo del circuito en carcasa impresa en PLA con sello de goma en la tapa superior y sellado en la ranura interna de cables.
* **Razón:** Proteger la placa Arduino Uno y la batería contra salpicaduras, inmersión y golpes dentro de una mochila de trekking.
* **Impacto:** Eliminación del riesgo de cortocircuito por filtración de agua durante la inmersión.

### Software

**De v1 a v2:**
* Incorporación de las librerías `OneWire.h` y `DallasTemperature.h` para lectura digital del sensor DS18B20.
* Implementación de ecuaciones de conversión de voltaje crudo (`V_TDS`, `V_TURB`) a unidades físicas (`ppm` y `NTU`) calibradas experimentalmente, más un ciclo de promediado de 10 muestras consecutivas y umbralización estricta bajo estándares AquaTabs/EPA/OMS (> 10 °C, < 5 NTU, < 500 ppm).

**De v2 a v3:**
* *(Completar si ajustaron parámetros de calibración o tiempos de espera tras las pruebas en la carcasa final).*

### Diseño 3D

**De v1 a v2:**
* Transición desde un boceto bidimensional a un modelo paramétrico 3D de paralelepípedo (70 × 120 × 270 mm) dividido en zona seca superior (con tapa de acceso rápido a batería) y faldón inferior abierto con orificio lateral de desaireación.

**De v2 a v3:**
* Impresión física en PLA, incorporación de sello de goma en tapa superior y sellado impermeable en el paso de cables entre cámaras *(agregar ajustes de tolerancia si los hubo al imprimir)*.

---

## Incorporación de Feedback

### Feedback del Avance #1 — Cambios en v2
1. **Revisión técnica con el Profesor Sebastián Duarte (encargado del DEC):** Se advirtió que la electrónica quedaba expuesta a riesgo de daño por contacto con agua durante la medición en terreno.
   * **Acción tomada:** Se rediseñó la arquitectura física del encapsulado para aislar e impermeabilizar completamente la cámara superior (Arduino, protoboard y batería) respecto de la zona inferior de inmersión de sensores.

### Feedback del Avance #2 — Cambios en v3
1. *(Agregar aquí los comentarios que les dejó el profesor Benjamín Gutiérrez o los ayudantes en la corrección del Avance 02).*
   * **Acción tomada:** *(Describir qué ajustaron para el Avance 3).*

### Feedback de Usuarios — Cambios en v3
1. **Resultados de encuesta pre-test (46 excursionistas):** El 65,2% declaró desconocer qué factores afectan a las pastillas potabilizadoras y reportó baja confianza (2,11/5) al evaluar el agua visualmente, valorando con 4,07/5 un dispositivo de confirmación simple.
   * **Acción tomada:** Se mantuvo una interfaz binaria ultraclarificada (LED Verde / LED Rojo sin pantallas complejas) calibrada directamente a los estándares de AquaTabs para evitar errores de interpretación en ruta. *(Agregar feedback de usuarios probando el prototipo físico en v3 si lo hicieron).*

---

## Métricas de Mejora

| Métrica | v1 | v2 | v3 | Mejora Total |
| :--- | :--- | :--- | :--- | :--- |
| **Variables medidas en tiempo real** | 0 (Simuladas) | 3 (Temp, TDS, NTU) | 3 (Temp, TDS, NTU) | +100% medición física |
| **Estabilización de lectura (muestras/ciclo)** | 1 lectura directa | 10 lecturas promediadas | 10 lecturas promediadas | Eliminación de ruido analógico |
| **Protección contra agua (IP / Sellado)** | Sin carcasa | Diseño CAD hermético | Carcasa PLA sellada | Protección completa electrónica |
| **Utilidad percibida por usuarios (1-5)** | 4.07 (Encuesta pre-test) | 4.07 | *(Completar post-test v3)* | Validado por 46 usuarios |

---

## Lecciones Aprendidas

### Técnicas
* Pasar de simulación en Wokwi a sensores reales exige calibrar experimentalmente los voltajes analógicos (`V_TDS` y `V_TURB`) y promediar múltiples lecturas (10 por ciclo) para evitar falsos positivos por ruido eléctrico.
* El diseño mecánico del encapsulado es tan crítico como el código: sin un orificio lateral de escape de aire en el faldón inferior, la presión hidrostática atrapa burbujas e impide que el agua toque los sensores.

### De Proceso
* Validar temprano los umbrales operativos con normativa real (AquaTabs, EPA y OMS) permitió acotar el alcance del prototipo y resolver un problema concreto sin necesidad de añadir pantallas LCD que encarecían y complicaban el sistema.

### De Trabajo en Equipo
* Dividir el desarrollo en frentes paralelos (simulación/código en Arduino IDE, calibración de sensores en laboratorio, modelado 3D en Fusion y validación con usuarios mediante encuestas) permitió avanzar de forma ordenada hacia la integración final.
