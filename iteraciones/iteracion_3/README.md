# Iteración 3 - Versión Final

## Información General

* **Fecha:** 22/11/2026
* **Versión:** v3.0
* **Estado:** Prototipo de alta resolución - Versión final
* **Avance asociado:** Avance #3

---

## Descripción

Versión final del prototipo (**Monitor de Calidad del Agua / Sistema E.V.A.**), incorporando todas las mejoras y refinamientos basados en el feedback de v2, validación con usuarios y pruebas experimentales. Sistema autónomo en terreno, reparable, documentado formalmente y conectado a la nube para respaldo histórico.

**Objetivos alcanzados:**
* Prototipo completamente funcional, autónomo y robusto
* Encapsulado final compactado con gemelo digital 3D, planos normalizados y renders
* Validación con usuarios del grupo objetivo (46 excursionistas encuestados) y protocolo experimental controlado
* Métricas de impacto ODS cuantificadas (ODS 6: Agua Limpia y Saneamiento)
* Arquitectura IoT operativa con respaldo en memoria interna EEPROM y dashboard en ThingSpeak

---

## Cambios Respecto a v2

### Hardware

**Mejoras implementadas:**
1. **Formalización electrónica y protección de señales en EasyEDA**
   * **Razón:** Garantizar la reproducibilidad eléctrica del circuito y proteger los pines del microcontrolador frente a corrientes excesivas o ruido en el bus de datos.
   * **Impacto:** Incorporación explícita de resistencia pull-up de `4,7 kΩ` en el sensor DS18B20, resistencias limitadoras de `220 Ω` en ambos LEDs y módulo cargador TP4056 (5 V, 1 A) para la batería Li-ion 18650.
2. **Priorización de conexiones desmontables (Diseño para la Reparación)**
   * **Razón:** Permitir el diagnóstico y reemplazo rápido de sensores dañados en terreno sin destruir la carcasa ni requerir soldadura.
   * **Impacto:** Uso de protoboard de 400 puntos con cables Dupont (jumpers) y tapa superior removible sin adhesivos permanentes.

**Cambios finales:**
* Elaboración de esquemático oficial en EasyEDA (`Proyecto_EVA`, V1.0)
* Documentación de Bill of Materials (BOM) completo con 13 ítems por un costo total de `$40.876 CLP`

### Software

**Nuevas funcionalidades:**
* Almacenamiento persistente en memoria interna **EEPROM** del Arduino Uno (capacidad de hasta 85 muestras de 12 bytes, con comandos seriales `'L'` para descargar historial CSV y `'B'` para borrar memoria)
* Desarrollo de script gateway en **Python** (`pyserial` y `requests`) que captura la telemetría serial USB y la sube automáticamente cada 15 segundos al canal público de **ThingSpeak** (ID `3588837`)

**Optimizaciones finales:**
* Estabilización automática de 5 segundos tras el encendido antes de registrar cada muestra en EEPROM
* Visualización remota en tiempo real mediante gráficos históricos e indicadores de umbral (*gauges*) en ThingSpeak

**Manejo de errores:**
* Detección de desconexión física del sensor de temperatura (`DEVICE_DISCONNECTED_C` / `-127 °C`), activando alerta roja de seguridad e impidiendo cálculos erróneos
* Limpieza de datos físicos forzando `0.00 NTU` ante cualquier valor negativo por dispersión óptica
* Control del límite de tasa de 15 segundos de la API gratuita de ThingSpeak desde Python

### Diseño Mecánico

**Encapsulado finalizado:**
* Diseño optimizado para impresión 3D en filamento PLA (`197 g`), reduciendo dimensiones exteriores a `52 × 100 × 253 mm` (`-42%` de volumen respecto a v2)
* Gemelo digital 3D completo en Autodesk Fusion 360 verificando volúmenes reales y ausencia de interferencias internas
* Sistema de montaje robusto con cámara electrónica superior aislada y faldón inferior protector con orificio de desaireación
* Accesibilidad para mantenimiento mediante tapa superior removible con pestaña de agarre
* Generación de planos técnicos ortogonales normalizados y renders fotorrealistas

---

## Fotos del Prototipo Final

Incluir en esta carpeta:
* `v3_prototipo_final_frontal.jpg` - Vista frontal del prototipo ensamblado en PLA
* `v3_prototipo_final_posterior.jpg` - Vista posterior y detalle del interruptor lateral SPDT
* `v3_interior_componentes.jpg` - Distribución interna de Arduino Uno, protoboard y batería 18650 bajo tapa removible
* `v3_render_gemelo3d.png` - Render fotorrealista del gemelo digital en Fusion 360
* `v3_detalle_sensores.jpg` - Cámara inferior de inmersión con sondas DS18B20, TDS y TSW-20M
* `v3_dashboard_thingspeak.png` - Captura de curvas históricas y gauges en ThingSpeak

---

## Resultados Finales

### Funcionalidad Completa
* [Logrado] Adquisición simultánea y estabilizada (promedio de 10 muestras) de temperatura, TDS y turbidez
* [Logrado] Sistema opera de forma autónoma en terreno sin intervención manual ni pantalla compleja
* [Logrado] Conectividad serial e IoT estable hacia ThingSpeak (cada 15 segundos) y respaldo local en EEPROM
* [Logrado] Interfaz binaria de usuario funcional (LED Verde / LED Rojo) calibrada bajo estándares AquaTabs/EPA/OMS
* [Logrado] Manejo robusto de errores por desconexión de sensores y aislamiento hídrico

### Testing y Validación con Usuarios

**Participantes:**
* `N = 46` usuarios encuestados (pre-test) + pruebas experimentales de laboratorio con muestras contrastantes
* **Perfil:** Excursionistas, montañistas y campistas de la Región Metropolitana que realizan actividades outdoor y utilizan pastillas potabilizadoras

**Resultados cuantitativos (Encuesta y Protocolo):**

| Métrica | Valor Obtenido | Observación |
| :--- | :--- | :--- |
| **Utilidad percibida del prototipo (1-5)** | `4,07 / 5,0` | 68,9% calificó con nota 4 o 5 |
| **Uso previo de pastillas potabilizadoras** | `78,3%` | Alta adopción del método químico en ruta |
| **Desconocimiento de factores críticos** | `65,2%` | No conocían efecto del frío o turbidez en la pastilla |
| **Precisión de clasificación binaria** | `100%` | Sin falsos positivos entre Muestra A y Muestra B |

**Feedback cualitativo más relevante:**
* **Positivo:** "El uso de dos luces (verde y rojo) elimina dudas al momento de echar la pastilla en ríos de montaña donde el agua parece limpia pero está muy helada."
* **Positivo:** "El tamaño compacto y el peso reducido permiten llevarlo en cualquier bolsillo de la mochila de trekking."
* **A mejorar:** "Incorporar un indicador visual de nivel de carga de la batería 18650 antes de salir a rutas de varios días."

---

## Validación de Impacto ODS

**ODS Seleccionado:** ODS 6 - Agua Limpia y Saneamiento (Meta 6.1: lograr el acceso universal y equitativo al agua potable segura y asequible).

**Métricas de Impacto:**
1. **Confiabilidad en la desinfección química en zonas sin cobertura NCh 409:**
   * **Baseline (sin prototipo):** Evaluación subjetiva visual (`2,11 / 5,0` de confianza percibida), con alto riesgo de falla de pastillas AquaTabs por temperaturas `< 10 °C` o sólidos `> 500 ppm` en aguas cristalinas.
   * **Con prototipo (valor medido):** Verificación objetiva de los 3 parámetros críticos en segundos (`100%` de detección en muestras de control y estrés).
   * **Mejora:** Reducción drástica del riesgo de consumo de agua mal desinfectada en rutas naturales de montaña.
2. **Accesibilidad económica de monitoreo multiparámetro:**
   * **Baseline:** Equipos comerciales multiparámetro de laboratorio/terreno superan los `$250.000 - $400.000
