# Testing y Validación - Documentación

## Contenido

Esta carpeta documenta los protocolos de prueba, los resultados experimentales y la validación con usuarios del proyecto **Monitor de Calidad del Agua**.

### Carpetas

* `datos/`  
  Registros cuantitativos obtenidos desde el Monitor Serial, exportación CSV de la memoria interna EEPROM y respaldos descargados desde el historial en la nube de **ThingSpeak**.

* `evidencia/`  
  Capturas de pantalla de las gráficas evolutivas, indicadores de umbral (*gauges*) en ThingSpeak, ejecución del script `subir_datos.py` y fotografías de las pruebas en laboratorio.

---

## Protocolo de Pruebas Experimentales

### Objetivo
Validar el funcionamiento integral del prototipo, verificando la adquisición continua y estable de los tres sensores (temperatura, TDS y turbidez), la correcta activación de las alertas locales (LED verde/rojo) según los umbrales operativos de las pastillas potabilizadoras **AquaTabs**, el almacenamiento local en memoria **EEPROM** y la transmisión persistente hacia el dashboard de **ThingSpeak**.

### Muestras de Prueba (Condiciones Controladas)
1. **Muestra A (Control Apto):** Agua potable de la llave a temperatura ambiente (`21,81 °C`), con niveles bajos de turbidez (`0,00 NTU`) y sólidos disueltos dentro de norma (`250,1 ppm`).
2. **Muestra B (Control No Apto):** Agua refrigerada con hielo, sal disuelta y partículas en suspensión (harina) para forzar simultáneamente temperaturas inferiores a `10 °C`, sólidos disueltos superiores a `500 ppm` y turbidez superior a `5 NTU`.

### Procedimiento de Ejecución
1. Encender el sistema mediante el interruptor lateral SPDT, conectar el prototipo al computador vía USB y abrir el Monitor Serial a 9600 baudios para verificar el inicio de la captura continua (filtro de promedio móvil de 10 lecturas por ciclo).
2. Sumergir la cámara inferior de sensores en la **Muestra A** durante 2 minutos, verificando el escape de aire por el orificio lateral, la estabilización de los valores en el Monitor Serial, el encendido del **LED Verde** y el guardado automático de la muestra en la memoria **EEPROM**.
3. Ejecutar el script de Python (`subir_datos.py`) para leer el registro serial de la EEPROM y transmitirlo a ThingSpeak, verificando su aparición en las gráficas históricas y en la zona verde de los *gauges*.
4. Enjuagar y secar los sensores, luego sumergirlos en la **Muestra B** durante 2 minutos, verificando la caída de temperatura, el aumento de TDS y turbidez, el cambio inmediato al **LED Rojo** y, tras ejecutar nuevamente el script de sincronización, el desplazamiento de los *gauges* hacia la zona roja de alerta en ThingSpeak.

### Criterios de Éxito
* Lectura estable y continua de los tres sensores sin interrupciones ni filtración de agua hacia la cámara electrónica superior.
* Clasificación binaria correcta (**LED Verde** en Muestra A; **LED Rojo** en Muestra B) en el 100% de las muestras estabilizadas.
* Registro exitoso de los datos en memoria EEPROM y posterior almacenamiento con marca de tiempo en ThingSpeak, visualizándose correctamente en los gráficos y *gauges*.

---

## Resultados Cuantitativos y Evidencia

### 1. Pruebas de Calibración y Estrés en Laboratorio (Avance #2)

| Prueba Realizada | Temperatura Medida | TDS Medido | Turbidez Medida | Voltajes Crudos | Respuesta LED |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Agua de la llave (Control Apto)** | 23,06 °C – 23,12 °C | 270,38 – 271,95 ppm | 0,00 NTU | V_TDS: 0,70 V / V_TURB: 4,28 V | **LED Verde** (Apta para pastilla) |
| **Agua helada con sal (Estrés No Apto)** | 2,88 °C – 5,50 °C | 749,82 – 844,50 ppm | 0,00 NTU | V_TDS: 1,09 V / V_TURB: 4,48 V | **LED Rojo** (No apta por frío y salinidad) |

### 2. Validación Final Integrada con EEPROM y ThingSpeak (Avance #3)

| Parámetro / Indicador | Muestra A (Control Apto) | Muestra B (Control No Apto) | Umbral Operativo (AquaTabs / EPA) | Resultado Esperado vs. Obtenido |
| :--- | :--- | :--- | :--- | :--- |
| **Temperatura (°C)** | 21,81 °C | 5,88 °C | > 10 °C | Coincide |
| **Sólidos Disueltos (ppm)** | 250,1 ppm | 892,33 ppm | < 500 ppm | Coincide |
| **Turbidez (NTU)** | 0,00 NTU | 403,06 NTU | < 5 NTU | Coincide |
| **Voltajes Crudos (Referencia)** | V_TDS: 0,63 V / V_TURB: 4,26 V | V_TDS: 1,25 V / V_TURB: 4,09 V | ADC 0–5 V | Coincide |
| **Respuesta Visual LED** | **LED Verde** | **LED Rojo** | 3/3 condiciones | Coincide |

### 3. Registros Exportados desde EEPROM hacia ThingSpeak (`subir_eva.py`)

| ID Registro ThingSpeak | Muestra | Temperatura (°C) | TDS (ppm) | Turbidez (NTU) | Voltaje TDS (V) | Voltaje Turbidez (V) | Estado LED |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **ID 1** | Muestra A (Agua de la llave) | 21,81 °C | 250,10 ppm | 0,00 NTU | 0,63 V | 4,26 V | **LED Verde** |
| **ID 2** | Muestra B (Agua fría + sal + harina) | 5,88 °C | 892,33 ppm | 403,06 NTU | 1,25 V | 4,09 V | **LED Rojo** |

* **Latencia local (LEDs):** Respuesta inmediata por ciclo de promediado (10 lecturas consecutivas).
* **Persistencia local (EEPROM):** Guardado automático tras 5 segundos de estabilización (capacidad de hasta 85 muestras).
* **Latencia cloud (ThingSpeak):** Sincronización mediante `sub`
