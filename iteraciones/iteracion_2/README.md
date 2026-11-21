# Iteración 2 - Primera Mejora Significativa

## Información General

* **Fecha:** 25/10/2026
* **Versión:** v2.0
* **Estado:** Prototipo funcional ensamblado en físico + Modelo CAD inicial
* **Avance asociado:** Avance #2

---

## Descripción

Segunda versión del prototipo (**Monitor de Calidad del Agua / Sistema E.V.A.**), incorporando feedback de la iteración 1 y del Avance #1. Incluye el salto desde simulación virtual al ensamblaje físico completo en protoboard con sensores sumergibles reales, calibración experimental en laboratorio y el primer modelado paramétrico en 3D del encapsulado.

**Objetivos de esta iteración:**
* Reemplazar las entradas simuladas de v1 por sensores físicos reales (temperatura, TDS y turbidez)
* Implementar las fórmulas de conversión matemática a `ppm` y `NTU` calibradas con agua potable
* Diseñar la primera arquitectura 3D del encapsulado dividido en zona electrónica hermética y falda protectora inferior
* Validar el circuito físico mediante pruebas de control y estrés en laboratorio

---

## Cambios Respecto a v1

### Hardware

**Agregado:**
* Placa Arduino Uno física, protoboard de 400 puntos, jumpers y resistencias de protección
* Sensor de Temperatura Sumergible DS18B20 (pin digital `D2`)
* Sensor de Sólidos Disueltos Totales TDS V1.0 (pin analógico `A0`) y Sensor de Turbidez Óptico TSW-20M (pin analógico `A1`)
* Batería recargable Li-ion 18650 con módulo de carga para operación autónoma sin PC

**Modificado:**
* Alimentación del sistema - Razón: Incorporación de batería interna 18650 para permitir autonomía energética en terreno manteniendo el modo USB de depuración por Monitor Serial.
* Distribución física de componentes - Razón: Separación estricta en dos cámaras (electrónica superior impermeabilizada y sensores en zona inferior) tras asesoría técnica con el Profesor Sebastián Duarte.

**Removido:**
* Potenciómetros simulados de Wokwi - Razón: Reemplazados por los sensores analógicos reales TDS V1.0 y TSW-20M.

### Software

**Nuevas funcionalidades:**
* Ecuaciones matemáticas de conversión desde voltaje crudo (`V_TDS` y `V_TURB`) a unidades físicas (`ppm` y `NTU`) con compensación térmica
* Calibración bajo estándares operativos de pastillas **AquaTabs** y normativa **EPA/OMS** (`Temperatura > 10 °C`, `Turbidez < 5 NTU`, `TDS < 500 ppm`)

**Optimizaciones:**
* Filtro de estabilización por promedio móvil de **10 lecturas consecutivas** por ciclo para eliminar fluctuaciones instantáneas de voltaje
* Telemetría serial a 9600 baudios imprimiendo simultáneamente voltajes crudos y valores convertidos

**Bugs corregidos:**
* Lecturas erráticas por ruido eléctrico en entradas analógicas al pasar de simulación virtual a sensores reales
* Valores negativos imposibles en el cálculo de turbidez (forzados a `0.00 NTU` como piso físico)

### Diseño Mecánico
* Primer diseño paramétrico de encapsulado en Autodesk Fusion (paralelepípedo de `70 × 120 × 270 mm`)
* Incorporación de tapa superior removible con sello de goma para mantenimiento de batería
* Diseño de faldón protector inferior abierto con orificio lateral de ventilación para escape de aire al sumergir

---

## Fotos del Prototipo v2

Incluir en esta carpeta:
* `v2_prototipo_completo.jpg` - Circuito físico ensamblado en protoboard con batería 18650 y sensores
* `v2_prueba_agua_llave.jpg` - Prueba de control en agua de la llave (~23,1 °C / 271 ppm / 0 NTU / LED Verde)
* `v2_prueba_agua_helada_sal.jpg` - Prueba de estrés con agua helada y sal (~3 °C / >750 ppm / LED Rojo)
* `v2_encapsulado_inicial.jpg` - Modelo 3D inicial del encapsulado en Autodesk Fusion (vistas exterior e interior)

---

## Resultados de Testing

### Funcionalidad Lograda
* [Logrado] Lectura estable y simultánea de los 3 sensores sumergibles reales en protoboard
* [Logrado] Clasificación binaria correcta en pruebas de laboratorio: LED Verde en agua de la llave (~23,1 °C, 271 ppm, 0 NTU) y LED Rojo en agua helada con sal (2,88–5,50 °C, 749–844 ppm)
* [Logrado] Transmisión continua de datos y voltajes crudos vía Monitor Serial (9600 baudios)
* [Parcial] Encapsulado 3D modelado digitalmente (pendiente de impresión física en PLA y compactación de volumen)

### Feedback del Avance #2

**Comentarios y observaciones técnicas:**
1. **Protección contra filtración de agua (Asesoría Prof. Sebastián Duarte - DEC):**
   * **Acción tomada:** Se definió impermeabilizar la cámara superior y el paso de cables hacia los sensores para evitar daño en la placa Arduino Uno.
2. **Refinamiento hacia versión final (Avance #3):**
   * **Acción tomada:** Planificar la compactación volumétrica del encapsulado 3D, formalizar el esquemático en EasyEDA, detallar el presupuesto (BOM) e incorporar almacenamiento histórico de datos (EEPROM y ThingSpeak).

### Testing y Validación con Usuarios (Pre-test)
* **Resultados cuantitativos (Encuesta estructurada a 46 excursionistas):**
  * Seguridad percibida al evaluar fuentes naturales actualmente: `2,67 / 5,0`
  * Capacidad percibida para identificar agua apta para pastillas: `2,11 / 5,0`
  * Utilidad percibida del prototipo propuesto: `4,07 / 5,0`
* **Feedback cualitativo:**
  * **Positivo:** Alta valoración de una señal binaria simple (LED verde/rojo) sin pantallas complejas para usar en ruta.
  * **A mejorar:** Un 65,2% desconocía los factores que afectan a las pastillas (frío/turbidez), reforzando la necesidad de calibrar estrictamente bajo estándares AquaTabs.

---

## Problemas Pendientes

1. **Problema 1: Encapsulado aún en fase CAD (sin manufactura física)**
   * **Descripción:** La carcasa de `70 × 120 × 270 mm` requiere optimizar su volumen interno y fabricarse en PLA para alojar la electrónica.
   * **Prioridad:** Alta
   * **Plan para v3:** Reducir dimensiones a `52 × 100 × 253 mm` mediante un gemelo 3D con volúmenes reales, diseñar tapa removible con pestaña (sin adhesivos permanentes) y generar planos técnicos normalizados.

2. **Problema 2: Falta de persistencia y visualización histórica de datos**
   * **Descripción:** Al apagar el prototipo o desconectar el Monitor Serial, los registros numéricos de las mediciones se pierden.
   * **Prioridad:** Media
   * **Plan para v3:** Implementar almacenamiento interno en memoria EEPROM (hasta 85 muestras) y desarrollar un script gateway en Python para subir datos automáticamente al dashboard público de ThingSpeak.

---

## Comparación v1 vs v2

| Aspecto | v1 | v2 | Mejora |
| :--- | :--- | :--- | :--- |
| **Sensores funcionales** | 1/3 reales (2 simulados con potenciómetros) | 3/3 físicos sumergibles (DS18B20, TDS, TSW-20M) | 100% hardware real |
| **Estabilización de señal** | 1 lectura directa | Promedio móvil de 10 lecturas consecutivas | Eliminación de ruido analógico |
| **Alimentación** | Simulación virtual | Autónoma con batería Li-ion 18650 | Portabilidad en terreno |
| **Encapsulado** | Boceto en papel | Modelo CAD 3D en Autodesk Fusion | Diseño estructural validado |
| **Testing** | Simulación en Wokwi | Pruebas de laboratorio (agua llave vs. helada/sal) | Validación física experimental |

---

## Plan para Iteración 3 (Versión Final)

### Mejoras Críticas

**Hardware:**
* [ ] Elaborar el esquemático electrónico formal en EasyEDA (especificando pull-up de `4,7 kΩ`, resistencias de `220 Ω` y módulo TP4056)
* [ ] Completar la tabla Bill of Materials (BOM) con costos detallados en CLP

**Software:**
* [ ] Integrar almacenamiento persistente en memoria interna EEPROM (hasta 85 muestras con exportación CSV)
* [ ] Desarrollar script gateway en Python para transmisión automática en tiempo real hacia ThingSpeak

**Diseño:**
* [ ] Compactar dimensiones del encapsulado a `52 × 100 × 253 mm` y validar interferencias con gemelo 3D
* [ ] Mejorar accesibilidad mediante tapa superior removible con pestaña (Diseño para la Reparación)
* [ ] Generar planos técnicos ortogonales normalizados y renders fotorrealistas

**Testing:**
* [ ] Ejecutar protocolo formal con muestras contrastantes (Muestra A Apta vs. Muestra B No Apta)
* [ ] Validar registro histórico y alertas virtuales en el dashboard público de ThingSpeak

---

## Archivos en esta Carpeta

* `v2_codigo.ino` - Código fuente de Arduino con conversión a ppm/NTU y filtro de 10 muestras
* `v2_esquema.png` - Esquema de conexiones y pruebas físicas en protoboard
* `v2_modelo3d.f3d` - Primer diseño 3D en Autodesk Fusion (`70 × 120 × 270 mm`)
* `v2_fotos/` - Fotografías del circuito físico y capturas del Monitor Serial
* `v2_feedback.pdf` - Compilación de observaciones técnicas y resultados de encuesta pre-test
