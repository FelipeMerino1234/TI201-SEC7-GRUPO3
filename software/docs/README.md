# Documentación de Software

## Contenido

### Diagramas de Flujo
Incluir diagramas de las funciones principales del sistema y de la arquitectura IoT (Adquisición -> Procesamiento en Arduino -> Gateway Python -> Nube ThingSpeak).

* **Formato:** PNG, PDF o draw.io (`arquitectura_iot.png`, `flujo_firmware.png`).

---

### Documentación de Funciones

Funciones Principales del firmware embebido en Arduino (`main.ino`) y del script gateway (`gateway_thingspeak.py`):

#### `setup()`
* **Propósito:** Inicializa la comunicación serial a 9600 baudios, arranca el bus OneWire del sensor de temperatura DS18B20, configura los pines digitales de salida para los LEDs (`D8` y `D9`) y habilita la resistencia pull-up interna (`INPUT_PULLUP`) en el pin `D3` para el interruptor lateral.
* **Parámetros:** Ninguno (`void`).
* **Retorna:** `void`.
* **Ejemplo de uso:**
```cpp
void setup() {
  Serial.begin(9600);
  sensorTemp.begin();
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
  pinMode(3, INPUT_PULLUP);
}
```

#### `loop()`
* **Propósito:** Verifica el estado del interruptor en el pin `D3` (deteniendo el sistema si está en pausa), toma 10 lecturas consecutivas de temperatura, TDS y turbidez para calcular sus promedios estabilizados, evalúa los umbrales operativos de AquaTabs (`Temp > 10 °C`, `Turbidez < 5 NTU`, `TDS < 500 ppm`), activa el LED correspondiente y transmite la trama de datos por puerto serial.
* **Parámetros:** Ninguno (`void`).
* **Retorna:** `void`.
* **Ejemplo de uso:**
```cpp
void loop() {
  if (digitalRead(3) == LOW) {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_ROJO, LOW);
    return;
  }
  // Lectura de sensores, promediado de 10 muestras y control de LEDs
}
```

#### `enviar_thingspeak()` (Script Gateway en Python)
* **Propósito:** Lee cada línea enviada por el Arduino Uno a través del puerto serial USB, extrae los valores numéricos de temperatura, TDS y turbidez, y los publica mediante una petición HTTP hacia la API de ThingSpeak (Canal ID `3588837`) respetando el intervalo de 15 segundos.
* **Parámetros:** `temperatura` (`float`), `tds` (`float`), `turbidez` (`float`), `apto` (`int`).
* **Retorna:** Código de estado HTTP de la respuesta de ThingSpeak (`int`).
* **Ejemplo de uso:**
```python
enviar_thingspeak(temperatura=23.12, tds=271.44, turbidez=0.00, apto=1)
```

---

## Manual de Instalación

1. **Instalación de Arduino IDE:** Descargar e instalar Arduino IDE 2.x en el computador y conectar la placa Arduino Uno vía cable USB.
2. **Instalación de librerías de Arduino:** Abrir el Gestor de Librerías (*Library Manager*) en Arduino IDE e instalar `OneWire` y `DallasTemperature`.
3. **Carga del firmware:** Abrir `src/main.ino`, seleccionar **Arduino Uno** y el puerto `COM` correspondiente en el menú **Herramientas**, y presionar **Subir (Upload)**.
4. **Configuración del entorno IoT (Python):** Instalar Python 3.8 o superior y ejecutar en la terminal `pip install pyserial requests` para habilitar la lectura serial y el envío hacia ThingSpeak.

---

## Manual de Operación

### Encendido del Sistema
1. Verificar que la batería recargable Li-ion 18650 tenga carga (o conectar el equipo vía USB para modo de depuración y envío de datos a ThingSpeak).
2. Accionar el interruptor lateral SPDT hacia la posición de encendido (abriendo el circuito del pin `D3` respecto a GND) para iniciar el ciclo de medición.

### Operación Normal
1. Sumergir la cámara inferior (faldón protector) del dispositivo en la fuente natural de agua, asegurando que el aire escape por el orificio lateral y que los tres sensores queden cubiertos.
2. Esperar el ciclo de estabilización (promedio de 10 lecturas consecutivas) y observar el indicador LED superior:
   * **LED Verde encendido:** El agua cumple simultáneamente con Temperatura > 10 °C, Turbidez < 5 NTU y TDS < 500 ppm; es apta para aplicar la pastilla potabilizadora AquaTabs.
   * **LED Rojo encendido:** Al menos un parámetro está fuera de rango; se debe extender el tiempo de desinfección por frío o buscar otra fuente de agua.
3. *(Opcional en laboratorio o post-ruta)* Conectar el dispositivo al computador vía USB y ejecutar `gateway_thingspeak.py` para visualizar y almacenar las curvas históricas en ThingSpeak.

### Apagado del Sistema
1. Retirar el prototipo del agua, enjuagar los sensores con agua limpia si estuvieron en agua turbia o salina y secarlos suavemente.
2. Cambiar el interruptor lateral SPDT a la posición de apagado/pausa (`D3` conectado a GND) para apagar los LEDs y conservar la carga de la batería 18650.

---

## Troubleshooting

### Problemas Comunes

#### Problema 1: Error de conexión serial o fallo al subir datos a ThingSpeak
* **Causa probable:** El puerto `COM` está ocupado por el Monitor Serial de Arduino IDE, el cable USB no transmite datos, o el script en Python envía peticiones con menos de 15 segundos de diferencia (límite de la API gratuita de ThingSpeak).
* **Solución:**
  1. Cerrar completamente el Monitor Serial de Arduino IDE antes de ejecutar el script en Python.
  2. Verificar en el Administrador de Dispositivos el número de puerto `COM` asignado al Arduino Uno y actualizarlo en el código Python.
  3. Confirmar que el retardo (`time.sleep`) entre envíos HTTP sea de al menos **15 segundos** y exista conexión a Internet en el computador gateway.

#### Problema 2: Sensor no responde o entrega lecturas erráticas (`-127 °C` o `0.00`)
* **Causa probable:** Desconexión de un jumper en la protoboard tras manipular el equipo, ausencia de la resistencia pull-up de `4,7 kΩ` en el sensor DS18B20, o burbujas de aire atrapadas dentro de la cámara inferior al sumergir el dispositivo.
* **Solución:**
  1. Retirar la tapa superior removible y revisar el firme calce de los jumpers en los pines `D2` (Temperatura), `A0` (TDS) y `A1` (Turbidez), además de la resistencia de `4,7 kΩ` entre datos y 5 V.
  2. Verificar que el orificio lateral de ventilación del faldón inferior esté libre de obstrucciones para permitir la salida del aire al sumergir el equipo.
