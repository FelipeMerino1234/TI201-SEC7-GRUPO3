# Bill of Materials (BOM)

## Formato del Archivo

El archivo BOM:

| Columna | Descripción | Ejemplo |
| :--- | :--- | :--- |
| Cantidad | Número de unidades | 1 |
| Componente | Nombre descriptivo | Placa Arduino Uno |
| Especificación | Detalles técnicos | Microcontrolador ATmega328P, 5V, 14 pines digitales y 6 análogos |
| Fabricante | Marca del componente | Arduino / Compatible R3 |
| Código/SKU | Identificador único | UNO-R3 / DS18B20 / SEN0189 / SEN0244 |
| Proveedor | Tienda/distribuidor | MCI Electronics / MechatronicStore / MercadoLibre |
| Precio Unitario | Costo por unidad (CLP) | $9.990 |
| Precio Total | Cantidad x Precio | $9.990 |
| Datasheet | Link a especificaciones | Ver enlaces de documentación técnica |

---

## Lista Detallada de Materiales

| Cantidad | Componente | Especificación Técnica | Precio Unitario (CLP) | Precio Total (CLP) |
| :--- | :--- | :--- | :--- | :--- |
| 1 | Placa Arduino Uno | Microcontrolador ATmega328P, 5V, 14 pines digitales y 6 análogos (compatible R3) | $9.990 | $9.990 |
| 1 | Sensor de Temperatura | DS18B20 sumergible en acero inoxidable, digital 1-Wire (-55 °C a 125 °C) | $2.990 | $2.990 |
| 1 | Sensor de Turbidez | Módulo óptico TSW-20M, alimentación 3,3V-5V, salida analógica | $8.200 | $8.200 |
| 1 | Sensor de TDS | Módulo TDS V1.0 con sonda impermeable, 3,3V-5,5V, rango 0-1000 ppm, salida analógica | $4.096 | $4.096 |
| 2 | Luces LED | Diodos LED estándar de 5 mm (1 verde, 1 rojo) | $100 | $200 |
| 1 | Interruptor | Interruptor deslizante/palanca SPDT de 3 pines, 2 posiciones | $400 | $400 |
| 1 | Batería y Módulo de carga | Batería recargable Li-ion 18650 (3,7V) + módulo cargador TP4056 (5V, 1A) | $4.990 | $4.990 |
| 1 | Placa de Pruebas | Protoboard de 400 puntos sin soldadura, paso estándar de 2,54 mm | $2.690 | $2.690 |
| 1 | Resistencia | 4.700 Ω (4,7 kΩ), 1/4 W (resistencia pull-up para DS18B20) | $150 | $150 |
| 2 | Resistencias | 220 Ω, 1/4 W (limitadoras de corriente para LEDs) | $100 | $200 |
| 197 g | Filamento PLA | Filamento termoplástico PLA de 1,75 mm para impresión 3D del encapsulado | $2.983 | $2.983 |
| 1 rollo | Cinta Americana | Cinta adhesiva reforzada (duct tape) de 48 mm, resistente a la humedad | $1.990 | $1.990 |
| 1 set | Jumpers | Cables Dupont macho-macho y macho-hembra, 20 cm, 26 AWG, paso 2,54 mm | $2.000 | $2.000 |

---

## Archivos a Incluir

* `bom_completo.xlsx` - Lista completa de materiales con columnas de proveedor, SKU y datasheets
* `bom_completo.pdf` - Versión PDF para visualización rápida
* `datasheets/` - Carpeta con hojas de datos técnicas (DS18B20, TSW-20M, TDS V1.0 y TP4056)

---

## Presupuesto Total

**Costo Total Estimado:** $40.876 CLP

### Desglose por Categoría

* **Microcontrolador:** $9.990 CLP
* **Sensores:** $15.286 CLP
* **Actuadores:** $200 CLP
* **Estructura/Encapsulado:** $4.973 CLP
* **Otros (Alimentación, prototipado y componentes pasivos):** $10.427 CLP
