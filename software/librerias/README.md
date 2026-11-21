# Librerías

## Librerías Estándar (Arduino IDE)

Instalar desde el Library Manager de Arduino IDE:

1. **OneWire** - v2.3.8 (o superior)
   * **Propósito:** Implementa el protocolo de comunicación digital 1-Wire necesario para establecer enlace de datos a través de un único pin (`D2`) con el sensor de temperatura sumergible DS18B20.
   * **Instalación:** `Sketch > Include Library > Manage Libraries > Buscar "OneWire"` (autor: Paul Stoffregen).

2. **DallasTemperature** - v3.9.0 (o superior)
   * **Propósito:** Permite solicitar lecturas y convertir directamente la señal digital del sensor DS18B20 a grados Celsius (°C) sin tener que manipular manualmente los registros del sensor.
   * **Instalación:** `Sketch > Include Library > Manage Libraries > Buscar "DallasTemperature"` (autor: Miles Burton).

*(Nota: Los módulos analógicos TDS V1.0 y Turbidez TSW-20M no requieren librerías externas en Arduino IDE, ya que se leen directamente mediante la función nativa `analogRead()` en los pines `A0` y `A1`).*

---

## Librerías Adicionales (Gateway IoT en Python)

Para ejecutar el script gateway en el computador que lee el puerto serial y envía los datos hacia ThingSpeak, instalar mediante `pip`:

1. **pyserial** - v3.5
   * **Propósito:** Habilita la lectura de tramas de texto en tiempo real desde el puerto serie USB conectado al Arduino Uno.
   * **Instalación:** `pip install pyserial`

2. **requests** - v2.31.0 (o superior)
   * **Propósito:** Realiza las peticiones HTTP hacia la API REST de ThingSpeak (Canal ID `3588837`) para almacenar y graficar las mediciones en la nube.
   * **Instalación:** `pip install requests`

---

## Librerías Personalizadas / Modificadas

Este proyecto utiliza exclusivamente librerías estándar oficiales para garantizar su reproducibilidad. En caso de respaldar copias locales de las librerías de Arduino en esta carpeta, mantener la siguiente estructura:

### Estructura

```text
librerias/
├── OneWire/
│   ├── OneWire.h
│   ├── OneWire.cpp
│   └── keywords.txt
└── DallasTemperature/
    ├── DallasTemperature.h
    ├── DallasTemperature.cpp
    └── keywords.txt
```

### Instalación Manual

```bash
# Copiar carpetas a Arduino libraries
cp -r OneWire DallasTemperature ~/Documents/Arduino/libraries/
```

---

## Dependencias Completas

Listado completo de todas las librerías necesarias para compilar el firmware y operar el ecosistema IoT:

| Librería | Versión | Entorno / Fuente | Obligatoria |
| :--- | :--- | :--- | :--- |
| `OneWire.h` | v2.3.8+ | Arduino Library Manager | Sí (Firmware) |
| `DallasTemperature.h` | v3.9.0+ | Arduino Library Manager | Sí (Firmware) |
| `pyserial` | v3.5 | Python Package Index (PyPI) | Solo para envío a ThingSpeak |
| `requests` | v2.31.0+ | Python Package Index (PyPI) | Solo para envío a ThingSpeak |
