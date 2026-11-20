# Testing y Validación - Documentación

## Contenido

Esta carpeta documenta los protocolos de prueba, los resultados experimentales y la validación con usuarios del proyecto **Monitor de Calidad del Agua (Sistema E.V.A.)**.

### Carpetas

* `datos/`  
  Registros cuantitativos obtenidos desde el Monitor Serial y respaldos descargados desde el historial en la nube de **ThingSpeak**.

* `evidencia/`  
  Capturas de pantalla de las gráficas evolutivas, indicadores de umbral (*gauges*) en ThingSpeak y fotografías de las pruebas en laboratorio.

---

## Protocolo de Pruebas Experimentales

### Objetivo
Validar el funcionamiento integral del prototipo, verificando la adquisición continua y estable de los tres sensores (temperatura, TDS y turbidez), la correcta activación de las alertas locales (LED verde/rojo) según los umbrales operativos de las pastillas potabilizadoras **AquaTabs**, y la transmisión y almacenamiento persistente en el dashboard de **ThingSpeak**.

### Muestras de Prueba (Condiciones Controladas)
1. **Muestra A (Control Apto):** Agua potable de la llave a temperatura ambiente (~23 °C), con niveles bajos de turbidez y sólidos disueltos dentro de norma.
2. **Muestra B (Control No Apto):** Agua refrigerada con hielo y sal disuelta para forzar simultáneamente temperaturas inferiores a `10 °C`, sólidos disueltos superiores a `500 ppm` y/o turbidez superior a `5 NTU`.

### Procedimiento de Ejecución
1. Conectar el prototipo al computador vía cable USB y ejecutar el script gateway en Python (`gateway_thingspeak.py`) para enlazar el puerto serial con ThingSpeak.
2. Encender el sistema mediante el interruptor lateral SPDT y verificar el inicio de la captura continua (filtro de promedio móvil de 10 lecturas por ciclo).
3. Sumergir la cámara inferior de sensores en la **Muestra A** durante 2 minutos, verificando el escape de aire por el orificio lateral, registrando los valores en el Monitor Serial y comprobando la actualización del dashboard (cada 15 segundos) y el encendido del **LED Verde**.
4. Enjuagar y secar los sensores, luego sumergirlos en la **Muestra B** durante 2 minutos, verificando la caída de temperatura, el aumento de TDS y el cambio inmediato al **LED Rojo** y a la alerta roja virtual en ThingSpeak.

### Criterios de Éxito
* Lectura estable y continua de los tres sensores sin interrupciones ni filtración de agua hacia la cámara electrónica superior.
* Clasificación binaria correcta (**LED Verde** en Muestra A; **LED Rojo** en Muestra B) en el 100% de las muestras estabilizadas.
* Registro exitoso de los datos con marca de tiempo en ThingSpeak y visualización en tiempo real en los gráficos y gauges.

---

## Resultados Cuantitativos y Evidencia

### 1. Pruebas de Calibración y Estrés en Laboratorio (Avance #2)

| Prueba Realizada | Temperatura Medida | TDS Medido | Turbidez Medida | Voltajes Crudos | Respuesta LED |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Agua de la llave (Control Apto)** | ~23,06 °C – 23,12 °C | ~270,38 – 271,95 ppm | 0,00 NTU | `V_TDS: 0.70V` / `V_TURB: 4.28V` | **LED Verde** (Apta para pastilla) |
| **Agua helada con sal (Estrés No Apto)** | 2,88 °C – 5,50 °C | 749,82 – 844,50 ppm | 0,00 NTU | `V_TDS: 1.09V` / `V_TURB: 4.48V` | **LED Rojo** (No apta por frío y salinidad) |

### 2. Validación Final Integrada con ThingSpeak (Avance #3)

| Parámetro / Indicador | Muestra A (Control Apto) | Muestra B (Control No Apto) | Umbral Operativo (AquaTabs / EPA) | Estado de Validación |
| :--- | :--- | :--- | :--- | :--- |
| **Temperatura (°C)** | *(Completar promedio final)* | *(Completar promedio final)* | `> 10 °C` | Detecta enfriamiento crítico |
| **Sólidos Disueltos (ppm)** | *(Completar promedio final)* | *(Completar promedio final)* | `< 500 ppm` | Detecta exceso de mineralización |
| **Turbidez (NTU)** | *(Completar promedio final)* | *(Completar promedio final)* | `< 5 NTU` | Valida claridad requerida por cloro |
| **Respuesta Visual LED** | **LED Verde** | **LED Rojo** | Binaria simultánea | Clasificación sin falsos positivos |

* **Latencia local (LEDs):** Respuesta inmediata por ciclo de promediado (10 lecturas consecutivas).
* **Latencia cloud (ThingSpeak):** Actualización cada **15 segundos** (límite de frecuencia de la API gratuita de ThingSpeak).
* **Repositorio de registros:** Canal Público ThingSpeak (ID: 3588837) -> `https://thingspeak.mathworks.com/channels/3588837`

---

## Validación de Usuario (Encuesta Pre-Test)

Para validar la pertinencia de la solución con usuarios reales en la Región Metropolitana, se aplicó una encuesta estructurada a **46 participantes** que realizan actividades outdoor (trekking, montañismo y camping):

* **Uso previo de pastillas potabilizadoras:** El **78,3%** declaró haber utilizado pastillas potabilizadoras en rutas naturales.
* **Desconocimiento de factores críticos:** Un **65,2%** indicó no conocer los factores físicos o químicos (como baja temperatura o turbidez) que pueden inhibir el funcionamiento de una pastilla potabilizadora (y un **28,3%** declaró no estar seguro).
* **Baja confianza en la evaluación actual:**
  * Seguridad al decidir si una fuente natural puede tratarse: **2,67 / 5,0** puntos en promedio.
  * Capacidad percibida para identificar si el agua es adecuada: **2,11 / 5,0** puntos en promedio.
* **Utilidad percibida del prototipo:** La valoración de contar con un dispositivo portátil que confirme en terreno si el agua reúne las condiciones para la pastilla obtuvo un promedio de **4,07 / 5,0** puntos (con un **68,9%** calificándolo con nota 4 o 5), respaldando la necesidad del sistema.

---

## Validación frente a la Problemática Original

Las pruebas demuestran que el prototipo resuelve directamente la brecha de seguridad en rutas de montaña de la Región Metropolitana (fuera del alcance de la norma sanitaria NCh 409):

1. **Detección de riesgos invisibles:** En las pruebas con agua helada y salina, la muestra se mantenía visualmente cristalina (`0,00 NTU`). Mediante la inspección visual habitual de los excursionistas, esta agua parecería apta para aplicar la pastilla; sin embargo, el dispositivo detectó el frío extremo (`< 10 °C`) y el exceso de sólidos disueltos (`> 500 ppm`), activando de inmediato la alerta roja.
2. **Toma de decisiones objetiva en ruta:** Permite al usuario saber con certeza si puede aplicar la pastilla con tiempo estándar (**LED Verde**), o si debe extender el tiempo de contacto químico por baja temperatura o buscar una fuente alternativa (**LED Rojo**).
