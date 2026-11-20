# Testing y Validación - Documentación

## Contenido

Esta carpeta documenta los protocolos de prueba, los resultados experimentales y la validación con usuarios del proyecto **Monitor de Calidad del Agua (Sistema E.V.A.)**[span_0](start_span)[span_0](end_span)[span_1](start_span)[span_1](end_span)[span_2](start_span)[span_2](end_span)[span_3](start_span)[span_3](end_span).

### Carpetas

* `datos/`  
  Registros cuantitativos obtenidos desde el Monitor Serial y respaldos descargados desde el historial en la nube de **ThingSpeak**[span_4](start_span)[span_4](end_span)[span_5](start_span)[span_5](end_span)[span_6](start_span)[span_6](end_span).

* `evidencia/`  
  Capturas de pantalla de las gráficas evolutivas, indicadores de umbral (*gauges*) en ThingSpeak y fotografías de las pruebas en laboratorio[span_7](start_span)[span_7](end_span)[span_8](start_span)[span_8](end_span)[span_9](start_span)[span_9](end_span).

---

## Protocolo de Pruebas Experimentales

### Objetivo
Validar el funcionamiento integral del prototipo, verificando la adquisición continua y estable de los tres sensores (temperatura, TDS y turbidez), la correcta activación de las alertas locales (LED verde/rojo) según los umbrales operativos de las pastillas potabilizadoras **AquaTabs**, y la transmisión y almacenamiento persistente en el dashboard de **ThingSpeak**[span_10](start_span)[span_10](end_span).

### Muestras de Prueba (Condiciones Controladas)
1. **Muestra A (Control Apto):** Agua potable de la llave a temperatura ambiente (~23 °C), con niveles bajos de turbidez y sólidos disueltos dentro de norma[span_11](start_span)[span_11](end_span).
2. **Muestra B (Control No Apto):** Agua refrigerada con hielo y sal disuelta para forzar simultáneamente temperaturas inferiores a `10 °C`, sólidos disueltos superiores a `500 ppm` y/o turbidez superior a `5 NTU`[span_12](start_span)[span_12](end_span).

### Procedimiento de Ejecución
1. Conectar el prototipo al computador vía cable USB y ejecutar el script gateway en Python (`gateway_thingspeak.py`) para enlazar el puerto serial con ThingSpeak[span_13](start_span)[span_13](end_span)[span_14](start_span)[span_14](end_span).
2. Encender el sistema mediante el interruptor lateral SPDT y verificar el inicio de la captura continua (filtro de promedio móvil de 10 lecturas por ciclo)[span_15](start_span)[span_15](end_span).
3. Sumergir la cámara inferior de sensores en la **Muestra A** durante 2 minutos, verificando el escape de aire por el orificio lateral, registrando los valores en el Monitor Serial y comprobando la actualización del dashboard (cada 15 segundos) y el encendido del **LED Verde**[span_16](start_span)[span_16](end_span)[span_17](start_span)[span_17](end_span).
4. Enjuagar y secar los sensores, luego sumergirlos en la **Muestra B** durante 2 minutos, verificando la caída de temperatura, el aumento de TDS y el cambio inmediato al **LED Rojo** y a la alerta roja virtual en ThingSpeak[span_18](start_span)[span_18](end_span).

### Criterios de Éxito
* Lectura estable y continua de los tres sensores sin interrupciones ni filtración de agua hacia la cámara electrónica superior[span_19](start_span)[span_19](end_span)[span_20](start_span)[span_20](end_span).
* Clasificación binaria correcta (**LED Verde** en Muestra A; **LED Rojo** en Muestra B) en el 100% de las muestras estabilizadas[span_21](start_span)[span_21](end_span).
* Registro exitoso de los datos con marca de tiempo en ThingSpeak y visualización en tiempo real en los gráficos y gauges[span_22](start_span)[span_22](end_span).

---

## Resultados Cuantitativos y Evidencia

### 1. Pruebas de Calibración y Estrés en Laboratorio (Avance #2)

| Prueba Realizada | Temperatura Medida | TDS Medido | Turbidez Medida | Voltajes Crudos | Respuesta LED |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Agua de la llave (Control Apto)** | ~23,06 °C – 23,12 °C[span_23](start_span)[span_23](end_span) | ~270,38 – 271,95 ppm[span_24](start_span)[span_24](end_span) | 0,00 NTU[span_25](start_span)[span_25](end_span) | `V_TDS: 0.70V` / `V_TURB: 4.28V`[span_26](start_span)[span_26](end_span) | **LED Verde** (Apta para pastilla)[span_27](start_span)[span_27](end_span) |
| **Agua helada con sal (Estrés No Apto)** | 2,88 °C – 5,50 °C[span_28](start_span)[span_28](end_span) | 749,82 – 844,50 ppm[span_29](start_span)[span_29](end_span) | 0,00 NTU[span_30](start_span)[span_30](end_span) | `V_TDS: 1.09V` / `V_TURB: 4.48V`[span_31](start_span)[span_31](end_span) | **LED Rojo** (No apta por frío y salinidad)[span_32](start_span)[span_32](end_span)[span_33](start_span)[span_33](end_span) |

### 2. Validación Final Integrada con ThingSpeak (Avance #3)

| Parámetro / Indicador | Muestra A (Control Apto) | Muestra B (Control No Apto) | Umbral Operativo (AquaTabs / EPA) | Estado de Validación |
| :--- | :--- | :--- | :--- | :--- |
| **Temperatura (°C)** | *(Completar promedio final)*[span_34](start_span)[span_34](end_span) | *(Completar promedio final)*[span_35](start_span)[span_35](end_span) | `> 10 °C`[span_36](start_span)[span_36](end_span) | Detecta enfriamiento crítico[span_37](start_span)[span_37](end_span) |
| **Sólidos Disueltos (ppm)** | *(Completar promedio final)*[span_38](start_span)[span_38](end_span) | *(Completar promedio final)*[span_39](start_span)[span_39](end_span) | `< 500 ppm`[span_40](start_span)[span_40](end_span) | Detecta exceso de mineralización[span_41](start_span)[span_41](end_span) |
| **Turbidez (NTU)** | *(Completar promedio final)*[span_42](start_span)[span_42](end_span) | *(Completar promedio final)*[span_43](start_span)[span_43](end_span) | `< 5 NTU`[span_44](start_span)[span_44](end_span) | Valida claridad requerida por cloro[span_45](start_span)[span_45](end_span) |
| **Respuesta Visual LED** | **LED Verde**[span_46](start_span)[span_46](end_span)[span_47](start_span)[span_47](end_span) | **LED Rojo**[span_48](start_span)[span_48](end_span)[span_49](start_span)[span_49](end_span) | Binaria simultánea[span_50](start_span)[span_50](end_span) | Clasificación sin falsos positivos[span_51](start_span)[span_51](end_span) |

* **Latencia local (LEDs):** Respuesta inmediata por ciclo de promediado (10 lecturas consecutivas)[span_52](start_span)[span_52](end_span)[span_53](start_span)[span_53](end_span).
* **Latencia cloud (ThingSpeak):** Actualización cada **15 segundos** (límite de frecuencia de la API gratuita de ThingSpeak)[span_54](start_span)[span_54](end_span).
* **Repositorio de registros:** [Canal Público ThingSpeak (ID: 3588837)](https://thingspeak.mathworks.com/channels/3588837)[span_55](start_span)[span_55](end_span)

---

## Validación de Usuario (Encuesta Pre-Test)

Para validar la pertinencia de la solución con usuarios reales en la Región Metropolitana, se aplicó una encuesta estructurada a **46 participantes** que realizan actividades outdoor (trekking, montañismo y camping)[span_56](start_span)[span_56](end_span)[span_57](start_span)[span_57](end_span):

* **Uso previo de pastillas potabilizadoras:** El **78,3%** declaró haber utilizado pastillas potabilizadoras en rutas naturales[span_58](start_span)[span_58](end_span).
* **Desconocimiento de factores críticos:** Un **65,2%** indicó no conocer los factores físicos o químicos (como baja temperatura o turbidez) que pueden inhibir el funcionamiento de una pastilla potabilizadora (y un **28,3%** declaró no estar seguro)[span_59](start_span)[span_59](end_span)[span_60](start_span)[span_60](end_span).
* **Baja confianza en la evaluación actual:**
  * Seguridad al decidir si una fuente natural puede tratarse: **2,67 / 5,0** puntos en promedio[span_61](start_span)[span_61](end_span).
  * Capacidad percibida para identificar si el agua es adecuada: **2,11 / 5,0** puntos en promedio[span_62](start_span)[span_62](end_span).
* **Utilidad percibida del prototipo:** La valoración de contar con un dispositivo portátil que confirme en terreno si el agua reúne las condiciones para la pastilla obtuvo un promedio de **4,07 / 5,0** puntos (con un **68,9%** calificándolo con nota 4 o 5), respaldando la necesidad del sistema[span_63](start_span)[span_63](end_span)[span_64](start_span)[span_64](end_span).

---

## Validación frente a la Problemática Original

Las pruebas demuestran que el prototipo resuelve directamente la brecha de seguridad en rutas de montaña de la Región Metropolitana (fuera del alcance de la norma sanitaria NCh 409)[span_65](start_span)[span_65](end_span)[span_66](start_span)[span_66](end_span)[span_67](start_span)[span_67](end_span):

1. **Detección de riesgos invisibles:** En las pruebas con agua helada y salina, la muestra se mantenía visualmente cristalina (`0,00 NTU`)[span_68](start_span)[span_68](end_span)[span_69](start_span)[span_69](end_span). Mediante la inspección visual habitual de los excursionistas, esta agua parecería apta para aplicar la pastilla; sin embargo, el dispositivo detectó el frío extremo (`< 10 °C`) y el exceso de sólidos disueltos (`> 500 ppm`), activando de inmediato la alerta roja[span_70](start_span)[span_70](end_span).
2. **Toma de decisiones objetiva en ruta:** Permite al usuario saber con certeza si puede aplicar la pastilla con tiempo estándar (**LED Verde**), o si debe extender el tiempo de contacto químico por baja temperatura o buscar una fuente alternativa (**LED Rojo**)[span_71](start_span)[span_71](end_span)[span_72](start_span)[span_72](end_span).
# Testing y Validación - Documentación

## Contenido

Esta carpeta documenta los protocolos de prueba, los resultados experimentales y la validación con usuarios del proyecto **Monitor de Calidad del Agua (Sistema E.V.A.)**[span_0](start_span)[span_0](end_span)[span_1](start_span)[span_1](end_span)[span_2](start_span)[span_2](end_span)[span_3](start_span)[span_3](end_span).

### Carpetas

* `datos/`  
  Registros cuantitativos obtenidos desde el Monitor Serial y respaldos descargados desde el historial en la nube de **ThingSpeak**[span_4](start_span)[span_4](end_span)[span_5](start_span)[span_5](end_span)[span_6](start_span)[span_6](end_span).

* `evidencia/`  
  Capturas de pantalla de las gráficas evolutivas, indicadores de umbral (*gauges*) en ThingSpeak y fotografías de las pruebas en laboratorio[span_7](start_span)[span_7](end_span)[span_8](start_span)[span_8](end_span)[span_9](start_span)[span_9](end_span).

---

## Protocolo de Pruebas Experimentales

### Objetivo
Validar el funcionamiento integral del prototipo, verificando la adquisición continua y estable de los tres sensores (temperatura, TDS y turbidez), la correcta activación de las alertas locales (LED verde/rojo) según los umbrales operativos de las pastillas potabilizadoras **AquaTabs**, y la transmisión y almacenamiento persistente en el dashboard de **ThingSpeak**[span_10](start_span)[span_10](end_span).

### Muestras de Prueba (Condiciones Controladas)
1. **Muestra A (Control Apto):** Agua potable de la llave a temperatura ambiente (~23 °C), con niveles bajos de turbidez y sólidos disueltos dentro de norma[span_11](start_span)[span_11](end_span).
2. **Muestra B (Control No Apto):** Agua refrigerada con hielo y sal disuelta para forzar simultáneamente temperaturas inferiores a `10 °C`, sólidos disueltos superiores a `500 ppm` y/o turbidez superior a `5 NTU`[span_12](start_span)[span_12](end_span).

### Procedimiento de Ejecución
1. Conectar el prototipo al computador vía cable USB y ejecutar el script gateway en Python (`gateway_thingspeak.py`) para enlazar el puerto serial con ThingSpeak[span_13](start_span)[span_13](end_span)[span_14](start_span)[span_14](end_span).
2. Encender el sistema mediante el interruptor lateral SPDT y verificar el inicio de la captura continua (filtro de promedio móvil de 10 lecturas por ciclo)[span_15](start_span)[span_15](end_span).
3. Sumergir la cámara inferior de sensores en la **Muestra A** durante 2 minutos, verificando el escape de aire por el orificio lateral, registrando los valores en el Monitor Serial y comprobando la actualización del dashboard (cada 15 segundos) y el encendido del **LED Verde**[span_16](start_span)[span_16](end_span)[span_17](start_span)[span_17](end_span).
4. Enjuagar y secar los sensores, luego sumergirlos en la **Muestra B** durante 2 minutos, verificando la caída de temperatura, el aumento de TDS y el cambio inmediato al **LED Rojo** y a la alerta roja virtual en ThingSpeak[span_18](start_span)[span_18](end_span).

### Criterios de Éxito
* Lectura estable y continua de los tres sensores sin interrupciones ni filtración de agua hacia la cámara electrónica superior[span_19](start_span)[span_19](end_span)[span_20](start_span)[span_20](end_span).
* Clasificación binaria correcta (**LED Verde** en Muestra A; **LED Rojo** en Muestra B) en el 100% de las muestras estabilizadas[span_21](start_span)[span_21](end_span).
* Registro exitoso de los datos con marca de tiempo en ThingSpeak y visualización en tiempo real en los gráficos y gauges[span_22](start_span)[span_22](end_span).

---

## Resultados Cuantitativos y Evidencia

### 1. Pruebas de Calibración y Estrés en Laboratorio (Avance #2)

| Prueba Realizada | Temperatura Medida | TDS Medido | Turbidez Medida | Voltajes Crudos | Respuesta LED |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Agua de la llave (Control Apto)** | ~23,06 °C – 23,12 °C[span_23](start_span)[span_23](end_span) | ~270,38 – 271,95 ppm[span_24](start_span)[span_24](end_span) | 0,00 NTU[span_25](start_span)[span_25](end_span) | `V_TDS: 0.70V` / `V_TURB: 4.28V`[span_26](start_span)[span_26](end_span) | **LED Verde** (Apta para pastilla)[span_27](start_span)[span_27](end_span) |
| **Agua helada con sal (Estrés No Apto)** | 2,88 °C – 5,50 °C[span_28](start_span)[span_28](end_span) | 749,82 – 844,50 ppm[span_29](start_span)[span_29](end_span) | 0,00 NTU[span_30](start_span)[span_30](end_span) | `V_TDS: 1.09V` / `V_TURB: 4.48V`[span_31](start_span)[span_31](end_span) | **LED Rojo** (No apta por frío y salinidad)[span_32](start_span)[span_32](end_span)[span_33](start_span)[span_33](end_span) |

### 2. Validación Final Integrada con ThingSpeak (Avance #3)

| Parámetro / Indicador | Muestra A (Control Apto) | Muestra B (Control No Apto) | Umbral Operativo (AquaTabs / EPA) | Estado de Validación |
| :--- | :--- | :--- | :--- | :--- |
| **Temperatura (°C)** | *(Completar promedio final)*[span_34](start_span)[span_34](end_span) | *(Completar promedio final)*[span_35](start_span)[span_35](end_span) | `> 10 °C`[span_36](start_span)[span_36](end_span) | Detecta enfriamiento crítico[span_37](start_span)[span_37](end_span) |
| **Sólidos Disueltos (ppm)** | *(Completar promedio final)*[span_38](start_span)[span_38](end_span) | *(Completar promedio final)*[span_39](start_span)[span_39](end_span) | `< 500 ppm`[span_40](start_span)[span_40](end_span) | Detecta exceso de mineralización[span_41](start_span)[span_41](end_span) |
| **Turbidez (NTU)** | *(Completar promedio final)*[span_42](start_span)[span_42](end_span) | *(Completar promedio final)*[span_43](start_span)[span_43](end_span) | `< 5 NTU`[span_44](start_span)[span_44](end_span) | Valida claridad requerida por cloro[span_45](start_span)[span_45](end_span) |
| **Respuesta Visual LED** | **LED Verde**[span_46](start_span)[span_46](end_span)[span_47](start_span)[span_47](end_span) | **LED Rojo**[span_48](start_span)[span_48](end_span)[span_49](start_span)[span_49](end_span) | Binaria simultánea[span_50](start_span)[span_50](end_span) | Clasificación sin falsos positivos[span_51](start_span)[span_51](end_span) |

* **Latencia local (LEDs):** Respuesta inmediata por ciclo de promediado (10 lecturas consecutivas)[span_52](start_span)[span_52](end_span)[span_53](start_span)[span_53](end_span).
* **Latencia cloud (ThingSpeak):** Actualización cada **15 segundos** (límite de frecuencia de la API gratuita de ThingSpeak)[span_54](start_span)[span_54](end_span).
* **Repositorio de registros:** [Canal Público ThingSpeak (ID: 3588837)](https://thingspeak.mathworks.com/channels/3588837)[span_55](start_span)[span_55](end_span)

---

## Validación de Usuario (Encuesta Pre-Test)

Para validar la pertinencia de la solución con usuarios reales en la Región Metropolitana, se aplicó una encuesta estructurada a **46 participantes** que realizan actividades outdoor (trekking, montañismo y camping)[span_56](start_span)[span_56](end_span)[span_57](start_span)[span_57](end_span):

* **Uso previo de pastillas potabilizadoras:** El **78,3%** declaró haber utilizado pastillas potabilizadoras en rutas naturales[span_58](start_span)[span_58](end_span).
* **Desconocimiento de factores críticos:** Un **65,2%** indicó no conocer los factores físicos o químicos (como baja temperatura o turbidez) que pueden inhibir el funcionamiento de una pastilla potabilizadora (y un **28,3%** declaró no estar seguro)[span_59](start_span)[span_59](end_span)[span_60](start_span)[span_60](end_span).
* **Baja confianza en la evaluación actual:**
  * Seguridad al decidir si una fuente natural puede tratarse: **2,67 / 5,0** puntos en promedio[span_61](start_span)[span_61](end_span).
  * Capacidad percibida para identificar si el agua es adecuada: **2,11 / 5,0** puntos en promedio[span_62](start_span)[span_62](end_span).
* **Utilidad percibida del prototipo:** La valoración de contar con un dispositivo portátil que confirme en terreno si el agua reúne las condiciones para la pastilla obtuvo un promedio de **4,07 / 5,0** puntos (con un **68,9%** calificándolo con nota 4 o 5), respaldando la necesidad del sistema[span_63](start_span)[span_63](end_span)[span_64](start_span)[span_64](end_span).

---

## Validación frente a la Problemática Original

Las pruebas demuestran que el prototipo resuelve directamente la brecha de seguridad en rutas de montaña de la Región Metropolitana (fuera del alcance de la norma sanitaria NCh 409)[span_65](start_span)[span_65](end_span)[span_66](start_span)[span_66](end_span)[span_67](start_span)[span_67](end_span):

1. **Detección de riesgos invisibles:** En las pruebas con agua helada y salina, la muestra se mantenía visualmente cristalina (`0,00 NTU`)[span_68](start_span)[span_68](end_span)[span_69](start_span)[span_69](end_span). Mediante la inspección visual habitual de los excursionistas, esta agua parecería apta para aplicar la pastilla; sin embargo, el dispositivo detectó el frío extremo (`< 10 °C`) y el exceso de sólidos disueltos (`> 500 ppm`), activando de inmediato la alerta roja[span_70](start_span)[span_70](end_span).
2. **Toma de decisiones objetiva en ruta:** Permite al usuario saber con certeza si puede aplicar la pastilla con tiempo estándar (**LED Verde**), o si debe extender el tiempo de contacto químico por baja temperatura o buscar una fuente alternativa (**LED Rojo**)[span_71](start_span)[span_71](end_span)[span_72](start_span)[span_72](end_span).
