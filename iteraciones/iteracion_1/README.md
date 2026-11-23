# Iteración 1 - Concepto Inicial

## Información General

* **Fecha:** 29/08/2026
* **Versión:** v1.0
* **Estado:** Prototipo alpha - Prueba de concepto y simulación
* **Avance asociado:** Planificación inicial / Avance #1

---

## Descripción

Primera versión del prototipo (**Detector de Potabilidad del Agua**), enfocada en definir la problemática en rutas de montaña de la Región Metropolitana (fuera del alcance de la norma sanitaria NCh 409) y validar la factibilidad técnica y conceptual de una solución portátil mediante simulación electrónica y bocetado estructural.

**Objetivo de esta iteración:**
* Probar la lógica de lectura de entradas digitales y analógicas mediante simulación en Wokwi
* Validar comunicación entre el microcontrolador y los indicadores visuales
* Demostrar el concepto de actuación binaria (LED verde / LED rojo) sin pantallas complejas
* Conceptualizar la arquitectura física dividida en cámara superior sellada y faldón inferior para sensores

---

## Componentes Utilizados

### Hardware (Simulado en Wokwi y Boceto Conceptual)
* **Microcontrolador:** Arduino Uno (simulado en plataforma Wokwi)
* **Sensores:**
  * Sensor de Temperatura Digital DS18B20 (pin digital `D2`)
  * Potenciómetro 1 emulando señal analógica de Sólidos Disueltos Totales - TDS (pin `A0`)
  * Potenciómetro 2 emulando señal analógica de Turbidez (pin `A1`)
* **Actuadores:**
  * LED Verde (pin `D8`) y LED Rojo (pin `D9`) con resistencias limitadoras
* **Otros:** Protoboard virtual, pulsador/interruptor de encendido (pin `D3` con `INPUT_PULLUP`) y boceto en papel de carcasa dividida en dos secciones

### Software
* **IDE:** Wokwi Arduino Simulator / Arduino IDE
* **Librerías:** `OneWire.h` y `DallasTemperature.h`
* **Versión código:** v1.0

---

## Fotos y Evidencias del Prototipo

Incluir en esta carpeta:
* `v1_boceto_conceptual.jpg` - Boceto inicial del dispositivo dividido en cámara electrónica superior y faldón inferior
* `v1_simulacion_wokwi.png` - Captura del circuito virtual en Wokwi (`M.C.A`) con potenciómetros y LEDs


---

## Resultados de Testing Inicial

### Funcionalidad Lograda
* [Logrado] Validación de lógica condicional (`if / else`) en simulación Wokwi para encender LED Verde o LED Rojo según umbrales
* [Logrado] Implementación del interruptor de encendido/pausa con resistencia pull-up interna (`INPUT_PULLUP` en pin `D3`)
* [No implementado en v1] Conversión matemática a unidades físicas reales (`ppm` y `NTU`) y calibración con agua real

### Problemas Identificados

1. **Problema 1: Diferencia entre potenciómetros simulados y sensores físicos**
   * **Descripción:** En Wokwi las entradas de TDS y turbidez se simularon con potenciómetros lineales básicos, sin reflejar las curvas de voltaje reales de los sensores sumergibles.
   * **Causa probable:** Limitación de componentes disponibles en el entorno de simulación virtual respecto a sensores analógicos de calidad de agua.
   * **Solución propuesta:** Adquirir los sensores físicos (TDS V1.0 y Turbidez TSW-20M), medir sus voltajes crudos en laboratorio y programar las ecuaciones polinómicas/cuadráticas de conversión.

2. **Problema 2: Vulnerabilidad de la electrónica frente al agua en terreno**
   * **Descripción:** Al proyectar el uso en ríos y esteros de montaña,
