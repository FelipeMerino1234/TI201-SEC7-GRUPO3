# Código Fuente

## Archivos Principales

### `main.ino`
Archivo principal del proyecto desarrollado en Arduino para el sistema de monitoreo de calidad de agua.

**Estructura:**
* **Setup:** Inicialización del puerto serial a 9600 baudios, inicialización del bus OneWire para el sensor de temperatura Dallas DS18B20, y configuración de los pines de salida para indicadores LED y de entrada con resistencia pull-up para el interruptor de encendido.
* **Loop:** Ciclo continuo de adquisición de datos que:
  - Verifica el estado del interruptor de seguridad en el pin 3.
  - Adquiere la temperatura ambiente/líquido con el sensor digital.
  - Realiza un sobremuestreo (10 lecturas filtradas) en los canales analógicos de TDS (Pin A0) y Turbidez (Pin A1).
  - Aplica compensación térmica a la lectura de TDS y calcula la concentración en partes por millón (ppm).
  - Aplica curvas de calibración para estimar la turbidez en unidades nefelométricas (NTU).
  - Emite telemetría por comunicación serial y activa indicadores lumínicos (LED verde para condiciones seguras, LED rojo para parámetros fuera de rango).

## Sensores y Hardware Asociado
* **Sensor de Temperatura:** DS18B20 (comunicación 1-Wire en pin digital 2).
* **Sensor de Sólidos Disueltos (TDS):** Entrada analógica en pin A0.
* **Sensor de Turbidez:** Entrada analógica en pin A1 con offset de calibración.
* **Indicadores:** LEDs de estado en pines 8 (Verde) y 9 (Rojo).
* **Interruptor de Control:** Switch conectado a pin 3 con `INPUT_PULLUP`.



### Monitor Serial
- Baudrate: 115200
- Mensajes informativos con prefijos:
  - `[INFO]` - Información general
  - `[ERROR]` - Errores
  - `[DEBUG]` - Debug
