# Software - Documentación

## Contenido

Esta carpeta contiene todo el código y documentación del software del proyecto **Monitor de Calidad del Agua (Sistema E.V.A.)**[span_10](start_span)[span_10](end_span).

### 📁 Carpetas

* `src/`  
  Código fuente del proyecto (`.ino` para Arduino Uno y script `.py` de enlace serial hacia ThingSpeak)[span_11](start_span)[span_11](end_span)[span_12](start_span)[span_12](end_span).

* `librerias/`  
  Librerías adicionales necesarias para el sensor digital de temperatura (`OneWire` y `DallasTemperature`)[span_13](start_span)[span_13](end_span).

* `docs/`  
  Documentación técnica del software, lógica de calibración y arquitectura de datos[span_14](start_span)[span_14](end_span)[span_15](start_span)[span_15](end_span)[span_16](start_span)[span_16](end_span).

---

## Stack Tecnológico

* **Plataforma:** Arduino Uno (ATmega328P) + PC Gateway (Python 3)[span_17](start_span)[span_17](end_span)[span_18](start_span)[span_18](end_span)
* **Lenguaje:** C/C++ (Firmware embebido) y Python (Transmisión IoT)[span_19](start_span)[span_19](end_span)
* **IDE:** Arduino IDE 2.x[span_20](start_span)[span_20](end_span)
* **Librerías principales:**
  * `OneWire.h` - Protocolo de comunicación digital 1-Wire (Arduino)[span_21](start_span)[span_21](end_span)[span_22](start_span)[span_22](end_span)
  * `DallasTemperature.h` - Lectura y conversión de temperatura del sensor DS18B20 (Arduino)[span_23](start_span)[span_23](end_span)
  * `pyserial` - Lectura de tramas de datos desde el puerto serial USB (Python)[span_24](start_span)[span_24](end_span)
  * `requests` - Envío de mediciones mediante peticiones HTTP a la API de ThingSpeak (Python)[span_25](start_span)[span_25](end_span)

---

## Instalación y Configuración

### 1. Instalar Arduino IDE
1. Descargar e instalar **Arduino IDE 2.x** desde el sitio oficial de Arduino.
2. Conectar la placa **Arduino Uno** al computador mediante cable USB.

### 2. Configurar Arduino Uno
1. Abrir Arduino IDE y seleccionar la placa en **Herramientas > Placa > Arduino AVR Boards > Arduino Uno**.
2. Seleccionar el puerto serie asignado (ej. `COM5` en Windows o `/dev/ttyUSB0` en Linux/macOS) en **Herramientas > Puerto**.

### 3. Instalar Librerías
En Arduino IDE, abrir el **Gestor de Librerías** (*Library Manager*), buscar e instalar `OneWire` y `DallasTemperature` (o copiar la carpeta `librerias/` en el directorio local de Arduino):
```bash
# Copiar librerías personalizadas
cp -r librerias/* ~/Arduino/libraries/
```
Para el módulo gateway en Python, instalar las dependencias desde terminal:
```bash
pip install pyserial requests
```

### 4. Cargar Código
1. Abrir `src/main.ino` (código fuente de Arduino) en Arduino IDE.
2. Verificar que estén seleccionadas la placa Arduino Uno y el puerto correcto.
3. Presionar **Verificar (Compilar)** y luego **Subir (Upload)**.
4. *(Opcional para registro en la nube)* Cerrar el Monitor Serial de Arduino IDE y ejecutar el script de Python (`python src/gateway_thingspeak.py`).

---

## Configuración de Parámetros

Para ajustar pines, constantes de calibración o la conexión hacia ThingSpeak, editar las siguientes constantes en el código:

```cpp
// Definición de Pines (Arduino Uno)
#define PIN_TEMPERATURA 2   // Sensor digital DS18B20 (OneWire)
#define PIN_INTERRUPTOR 3   // Interruptor SPDT (INPUT_PULLUP)
#define PIN_TDS A0          // Sensor analógico TDS V1.0
#define PIN_TURBIDEZ A1     // Sensor analógico Turbidez TSW-20M
#define LED_VERDE 8         // Indicador agua apta
#define LED_ROJO 9          // Indicador agua no apta

// Parámetros de Muestreo y Umbrales AquaTabs
#define MUESTRAS_PROMEDIO 10 // Filtro de estabilización (10 lecturas por ciclo)
#define TEMP_MINIMA 10.0     // Umbral mínimo en °C
#define TURBIDEZ_MAXIMA 5.0  // Umbral máximo en NTU
#define TDS_MAXIMO 500.0     // Umbral máximo en ppm
```

---

## Arquitectura del Software

El sistema opera bajo una arquitectura de flujo continuo en 4 etapas que combina procesamiento local autónomo en terreno y respaldo en la nube al conectar el equipo vía USB[span_26](start_span)[span_26](end_span)[span_27](start_span)[span_27](end_span):

```text
[Sensores: DS18B20, TDS, TSW-20M] 
        │
        ▼ (Lectura ADC / OneWire)
[Arduino Uno: Promedio 10 muestras + Evaluación Umbrales] ──► [LED Verde / LED Rojo]
        │
        ▼ (Puerto Serial USB - 9600 baudios)
[PC Gateway: Script Python (pyserial + requests)]
        │
        ▼ (HTTP API cada 15 segundos)
[Nube ThingSpeak: Dashboard, Gauges e Historial CSV]
```

### Módulos Principales

1. **Inicialización** - Configuración de comunicación serial (`9600 baudios`), bus `OneWire` del sensor de temperatura, pines de salida para LEDs (`D8`, `D9`) e interruptor en modo `INPUT_PULLUP` (`D3`)[span_28](start_span)[span_28](end_span).
2. **Lectura de Sensores** - Captura continua en tiempo real de temperatura (°C), voltaje de sólidos disueltos (`V_TDS` en `A0`) y voltaje de turbidez (`V_TURB` en `A1`)[span_29](start_span)[span_29](end_span)[span_30](start_span)[span_30](end_span)[span_31](start_span)[span_31](end_span).
3. **Procesamiento** - Aplicación de ecuaciones de calibración a unidades físicas (`ppm` y `NTU`), cálculo de promedio móvil de 10 lecturas consecutivas y evaluación lógica simultánea (`Temp > 10 °C`, `Turbidez < 5 NTU`, `TDS < 500 ppm`)[span_32](start_span)[span_32](end_span)[span_33](start_span)[span_33](end_span)[span_34](start_span)[span_34](end_span).
4. **Actuación** - Control binario inmediato mediante indicadores luminosos: encendido de `LED_VERDE` (`D8`) si todos los parámetros son seguros, o `LED_ROJO` (`D9`) si al menos uno excede el límite[span_35](start_span)[span_35](end_span)[span_36](start_span)[span_36](end_span).
5. **Comunicación** - Transmisión de tramas por puerto serie USB hacia un script gateway en Python que publica las mediciones en **ThingSpeak**[span_37](start_span)[span_37](end_span).

---

## API / Endpoints (Integración Cloud ThingSpeak)

Dado que el microcontrolador **Arduino Uno** no posee módulo WiFi nativo, la conectividad web se realiza mediante un script gateway en **Python** conectado a la API REST de **ThingSpeak** (Canal público ID: `3588837`)[span_38](start_span)[span_38](end_span)[span_39](start_span)[span_39](end_span):

| Endpoint | Método | Descripción |
| :--- | :--- | :--- |
| `https://api.thingspeak.com/update` | `GET` / `POST` | Envía cada 15 segundos los valores de Temperatura (`field1`), TDS (`field2`), Turbidez (`field3`) y estado de aptitud (`field4`) usando la `Write API Key`[span_40](start_span)[span_40](end_span)[span_41](start_span)[span_41](end_span). |
| `https://thingspeak.mathworks.com/channels/3588837` | `GET` | Acceso público al dashboard en tiempo real con indicadores de umbral (*gauges*), alertas virtuales y descarga de historial[span_42](start_span)[span_42](end_span). |
