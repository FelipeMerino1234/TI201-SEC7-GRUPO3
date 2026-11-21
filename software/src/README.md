# Código Fuente

## Archivos Principales

### [`main.ino`](main.ino)
Archivo principal del firmware desarrollado en C++ (Arduino IDE) para el microcontrolador Arduino Uno encargado de la adquisición, filtrado, almacenamiento interno en EEPROM y evaluación local en terreno[cite: 37, 71].

**Estructura:**
* **Librerías utilizadas:** `OneWire.h`, `DallasTemperature.h` y `EEPROM.h` (nativa de Arduino para almacenamiento persistente sin batería)[cite: 71].
* **Setup:** Inicialización del puerto serial a 9600 baudios, inicialización del bus OneWire para el sensor de temperatura Dallas DS18B20, configuración de los pines de salida para indicadores LED (`D8`, `D9`), configuración de entrada con resistencia pull-up interna (`INPUT_PULLUP`) para el interruptor lateral (`D3`) y recuperación del contador de muestras guardadas en EEPROM[cite: 71].
* **Loop:** Ciclo continuo de adquisición de datos (cada 1 segundo) que[cite: 71]:
  * Escucha comandos por puerto serial desde el PC (`'L'` para descargar historial CSV desde EEPROM; `'B'` para borrar memoria)[cite: 71].
  * Verifica el estado del interruptor de seguridad en el pin `D3` (si está en `LOW`, apaga ambos LEDs, reinicia el estado de guardado y detiene la medición)[cite: 71].
  * Adquiere la temperatura del líquido en grados Celsius (°C) mediante el sensor digital DS18B20, verificando que el sensor no esté desconectado (`DEVICE_DISCONNECTED_C`)[cite: 71].
  * Realiza un sobremuestreo (filtro de promedio móvil de 10 lecturas consecutivas cada 5 ms) en los canales analógicos de TDS (`A0`) y Turbidez (`A1`)[cite: 71].
  * Aplica compensación térmica a la lectura de voltaje de TDS y calcula la concentración en partes por millón (`ppm`)[cite: 71].
  * Aplica offset de calibración (`+0.74 V`) y ecuación cuadrática del fabricante al voltaje de turbidez para estimar las unidades nefelométricas (`NTU`)[cite: 71].
  * Evalúa simultáneamente los umbrales operativos calibrados para pastillas **AquaTabs** (`Temperatura > 10 °C`, `Turbidez < 5 NTU` y `TDS < 500 ppm`)[cite: 38, 39, 71].
  * Emite telemetría por comunicación serial USB, activa los indicadores lumínicos (**LED Verde** si cumple las tres condiciones; **LED Rojo** si al menos un parámetro está fuera de rango) y guarda automáticamente 1 registro estable en memoria **EEPROM** (capacidad máxima de 85 muestras de 12 bytes) tras 5 segundos de estabilización[cite: 71].

### `gateway_thingspeak.py`
Script puente (Gateway IoT) desarrollado en Python 3 que conecta el dispositivo con la nube al vincularlo vía USB a un computador[cite: 39, 49].

**Estructura:**
* **Conexión Serial:** Abre el puerto `COM` asignado al Arduino Uno a 9600 baudios mediante la librería `pyserial` y lee en tiempo real las tramas emitidas por `main.ino`[cite: 39, 49, 71].
* **Procesamiento y Evaluación:** Extrae los valores numéricos de Temperatura (°C), TDS (ppm) y Turbidez (NTU), determinando el estado binario de aptitud del agua[cite: 39].
* **Transmisión Cloud:** Publica los registros mediante peticiones HTTP (`requests`) hacia la API de **ThingSpeak** (Canal público ID `3588837`) respetando el intervalo de actualización de **15 segundos** para almacenar el historial con fecha y hora y alimentar las gráficas y gauges del dashboard[cite: 40, 48, 49].

---

## Sensores y Hardware Asociado

* **Sensor de Temperatura:** DS18B20 (comunicación digital 1-Wire en pin `D2` con resistencia pull-up de `4,7 kΩ`)[cite: 42].
* **Sensor de Sólidos Disueltos (TDS):** Módulo TDS V1.0 con sonda impermeable en entrada analógica `A0`[cite: 41, 42].
* **Sensor de Turbidez:** Módulo óptico TSW-20M en entrada analógica `A1` con offset de calibración (`+0.74 V`)[cite: 41, 42, 71].
* **Indicadores:** Diodos LED de estado en pines digitales `D8` (Verde) y `D9` (Rojo) con resistencias limitadoras de `220 Ω`[cite: 42].

