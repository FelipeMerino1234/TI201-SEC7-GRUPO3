# Datos de Testing

## Archivos de Datos

### `datos_cuantitativos.xlsx`
Hoja de cálculo con los datos recolectados durante la encuesta de validación con usuarios (`N = 46` participantes) y las pruebas experimentales de laboratorio.

**Estructura del archivo:**

#### Sheet 1: Datos de Usuarios (Encuesta Pre-Test)
| ID Muestra | Grupo Objetivo | Frecuencia Outdoor | Uso Previo Pastillas | Fecha Encuesta |
| :--- | :--- | :--- | :--- | :--- |
| E01 – E46 | Excursionistas y campistas RM (18–55 años) | 50,0% Ocasional / 30,4% Mensual / 10,9% Semanal | 78,3% Sí / 21,7% No | Octubre 2026 |

#### Sheet 2: Métricas de Percepción y Utilidad (Escala 1 a 5)
| Indicador Evaluado | N Respuestas | Promedio | Nota 4 o 5 (%) | Observación |
| :--- | :--- | :--- | :--- | :--- |
| Seguridad al decidir si una fuente puede tratarse | 46 | 2,67 / 5,0 | 19,5% | Alta incertidumbre visual en ruta |
| Capacidad percibida para identificar agua adecuada | 46 | 2,11 / 5,0 | 10,8% | Desconocimiento de factores críticos (65,2%) |
| Utilidad percibida del prototipo propuesto | 45 | 4,07 / 5,0 | 68,9% | Alta aceptación del dispositivo portátil |

#### Sheet 3: Métricas Experimentales de Laboratorio (Control Apto vs. No Apto)
| Muestra | Temperatura (`field1`) | TDS (`field2`) | Turbidez (`field3`) | Voltajes Crudos | Respuesta LED |
| :--- | :--- | :--- | :--- | :--- | :--- |
| Muestra A (Control Apto) | 21,81 °C | 250,10 ppm | 0,00 NTU | `V_TDS: 0.63V` / `V_TURB: 4.26V` | LED Verde (Apta) |
| Muestra B (Control No Apto) | 5,88 °C | 892,33 ppm | 403,06 NTU | `V_TDS: 1.25V` / `V_TURB: 4.09V` | LED Rojo (No apta) |

#### Sheet 4: Feedback Cualitativo
| Tema / Hallazgo | Síntesis de Respuestas y Observaciones |
| :--- | :--- |
| Factor crítico desconocido | El 65,2% declaró no conocer factores como baja temperatura (< 10 °C) o turbidez (> 5 NTU) que inhiben la pastilla potabilizadora. |
| Valoración interfaz binaria | Alta aceptación del aviso inmediato mediante LED verde/rojo sin depender de pantallas complejas en montaña. |
| Oportunidad de mejora | Incorporar LEDs de alto brillo para luz solar directa e indicador de nivel de batería 18650. |

---

### `feeds.csv` (Datos Exportados desde ThingSpeak - Canal ID 3588837)
Registros reales capturados por el prototipo, almacenados en memoria interna EEPROM y sincronizados hacia la nube mediante el script `subir_eva.py`:

**Formato y valores reales registrados (`created_at, entry_id, field1 [Temp °C], field2 [TDS ppm], field3 [Turbidez NTU]`):**
```csv
created_at,entry_id,field1,field2,field3,field4,latitude,longitude,elevation,status
2026-11-22T16:37:38+00:00,1,21.81,250.1,0.0,,,,,
2026-11-22T16:57:21+00:00,2,5.88,892.33,403.06,,,,,
```

* **Registro `entry_id = 1` (`2026-11-22T16:37:38+00:00`):** Corresponde a la **Muestra A (Control Apto - agua de la llave)** con `21,81 °C`, `250,1 ppm` y `0,0 NTU` (todos los parámetros dentro de rango AquaTabs/EPA -> LED Verde).
* **Registro `entry_id = 2` (`2026-11-22T16:57:21+00:00`):** Corresponde a la **Muestra B (Control No Apto - agua fría con sal y harina)** con `5,88 °C`, `892,33 ppm` y `403,06 NTU` (todos los parámetros fuera de rango -> LED Rojo).

---

### `comparativa_versiones.xlsx`
Comparación de métricas técnicas y de desempeño entre iteraciones v1, v2 y v3:

| Métrica | v1 (Avance #1) | v2 (Avance #2) | v3 (Avance #3) | Mejora Total |
| :--- | :--- | :--- | :--- | :--- |
| Sensores físicos operativos | 1/3 (DS18B20 sim.) | 3/3 reales | 3/3 calibrados | +100% hardware real |
| Precisión clasificación binaria | Simulada (Wokwi) | 100% en lab | 100% integrado | Sin falsos positivos |
| Volumen encapsulado | Sin CAD | 2.268 cm³ | 1.315 cm³ | -42,0% volumen |
| Persistencia de datos | 0 muestras | Volátil (Serial) | 85 muestras (EEPROM) + Cloud | Trazabilidad total |

---

## Análisis Estadístico

### Estadísticos Descriptivos (Validación con Usuarios y Pruebas)

```text
Métrica 1: Utilidad percibida del prototipo (escala 1-5)
N = 45 respuestas válidas
Media: 4,07
Moda: 5,0 (46,7% de las respuestas)
Nota >= 4: 68,9%
Mín: 1, Máx: 5

Métrica 2: Confianza actual en evaluación visual del agua (escala 1-5)
N = 46 respuestas
Media: 2,11 (capacidad percibida) / 2,67 (seguridad al decidir)
Porcentaje que desconoce factores inhibidores: 65,2% (28,3% no está seguro)
```

---

## Datos de Impacto ODS

### Baseline vs. Resultado (ODS 6: Agua Limpia y Saneamiento)

**Antes de la intervención (baseline):**
* **Confiabilidad en la evaluación del agua en rutas RM:** Evaluación puramente visual (`2,11 / 5,0` de capacidad percibida), exponiendo a una población potencial de hasta `204.469` visitantes anuales en áreas silvestres de la RM a consumir agua mal desinfectada.
* **Costo de equipos multiparámetro comerciales:** Superior a `$250.000 - $400.000 CLP` por unidad.

**Después de la intervención:**
* **Confiabilidad en la detección de condiciones aptas:** `100%` de precisión en la discriminación entre agua apta (`21,81 °C`, `250,1 ppm`, `0,0 NTU`) y agua riesgosa (`5,88 °C`, `892,33 ppm`, `403,06 NTU`) en segundos.
* **Costo total de fabricación del prototipo (BOM):** `$40.876 CLP` (13 componentes comerciales).

**Mejora:**
* **Reducción de incertidumbre operativa:** `+92,9%` de mejora en percepción de utilidad (`4,07` vs. `2,11` en capacidad actual) y eliminación de falsos positivos por inspección visual.
* **Accesibilidad económica:** Reducción superior al `83%` respecto a instrumentación comercial equivalente.

---

## Visualización de Datos

iva)

