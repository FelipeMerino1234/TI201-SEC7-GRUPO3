# Software - Documentación

## Contenido

Esta carpeta contiene todo el código y documentación del software del proyecto **Monitor de Calidad del Agua**.

### Carpetas

* `src/`  
  Código fuente del proyecto (`.ino` para Arduino Uno y script `.py` de enlace serial hacia ThingSpeak).

* `librerias/`  
  Librerías adicionales necesarias para el sensor digital de temperatura (`OneWire` y `DallasTemperature`).

* `docs/`  
  Documentación técnica del software, lógica de calibración y arquitectura de datos.

---

## Stack Tecnológico

* **Plataforma:** Arduino Uno (ATmega328P) + PC Gateway (Python 3)
* **Lenguaje:** C/C++ (Firmware embebido) y Python (Transmisión IoT)
* **IDE:** Arduino IDE 2.x
* **Librerías principales:**
  * `OneWire.h` - Protocolo de comunicación digital 1-Wire (Arduino)
  * `DallasTemperature.h` - Lectura y conversión de temperatura del sensor DS18B20 (Arduino)
  * `pyserial` - Lectura de tramas de datos desde el puerto serial USB (Python)
  * `requests` - Envío de mediciones mediante peticiones HTTP a la API de ThingSpeak (Python)

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

El sistema opera bajo una arquitectura de flujo continuo en 4 etapas que combina procesamiento local autónomo en terreno y respaldo en la nube al conectar el equipo vía USB:

```text
[Sensores: DS18B20, TDS, TSW-20M] 
        |
        v (Lectura ADC / OneWire)
[Arduino Uno: Promedio 10 muestras + Evaluación Umbrales] --> [LED Verde / LED Rojo]
        |
        v (Puerto Serial USB - 9600 baudios)
[PC Gateway: Script Python (pyserial + requests)]
        |
        v (HTTP API cada 15 segundos)
[Nube ThingSpeak: Dashboard, Gauges e Historial CSV]
```

### Módulos Principales

1. **Inicialización** - Configuración de comunicación serial (`9600 baudios`), bus `OneWire` del sensor de temperatura, pines de salida para LEDs (`D8`, `D9`) e interruptor en modo `INPUT_PULLUP` (`D3`).
2. **Lectura de Sensores** - Captura continua en tiempo real
