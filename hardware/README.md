# Hardware - Documentación

## Contenido

Esta carpeta contiene toda la documentación técnica del hardware del proyecto **Monitor de Calidad del Agua (Sistema E.V.A.)**.

### 📁 Carpetas

* `esquemas/`  
  Diagramas de circuitos y esquemáticos formales del sistema exportados desde EasyEDA (`esquematico.pdf`) y simulación en Wokwi.

* `bom/`  
  Bill of Materials (Lista completa de materiales, especificaciones técnicas y costos asociados en CLP).

* `fotos/`  
  Fotografías de alta resolución del prototipo físico ensamblado (vistas superior, inferior y lateral) y pruebas en laboratorio.

---

## Instrucciones de Ensamble

### Componentes Principales

1. **Placa Arduino Uno (R3)** - Microcontrolador ATmega328P (5 V) encargado de procesar las señales de los sensores, calcular el promedio móvil de 10 lecturas y controlar las alertas visuales.
2. **Sensor de Temperatura Sumergible (DS18B20)** - Sensor digital 1-Wire en acero inoxidable (-55 °C a 125 °C) conectado al pin digital `D2` con resistencia pull-up de `4,7 kΩ` para medir temperatura en °C.
3. **Sensor de Sólidos Disueltos Totales (TDS V1.0)** - Módulo con sonda impermeable (0–1000 ppm) conectado al pin analógico `A0` para medir sales y minerales disueltos en ppm.
4. **Sensor de Turbidez Óptico (TSW-20M)** - Módulo óptico conectado al pin analógico `A1` para evaluar partículas suspendidas en NTU mediante un haz de luz.
5. **Indicadores LED (Verde y Rojo) y Resistencias** - Diodos LED de 5 mm con resistencias limitadoras de `220 Ω`: LED Verde (pin `D8`) indica agua apta para pastilla AquaTabs; LED Rojo (pin `D9`) alerta que al menos un parámetro está fuera de rango.
6. **Interruptor SPDT y Sistema de Alimentación (Batería 18650 + TP4056)** - Interruptor deslizante de 3 pines (pin `D3` con `INPUT_PULLUP`) y batería recargable Li-ion 18650 (3,7 V) con módulo cargador TP4056 (5 V, 1 A).

### Pasos de Ensamblaje

1. **Montaje del circuito base:** Conectar la protoboard de 400 puntos, las dos resistencias limitadoras de `220 Ω` para los LEDs (Verde al pin `D8` y Rojo al pin `D9`), la resistencia pull-up de `4,7 kΩ` para el sensor DS18B20 y el interruptor SPDT al pin `D3` y GND.
2. **Conexión de sensores:** Conectar el sensor de temperatura DS18B20 al pin digital `D2`, el sensor TDS V1.0 al pin analógico `A0` y el sensor de turbidez TSW-20M al pin analógico `A1`, alimentándolos desde el riel de 5 V y GND común.
3. **Integración en el encapsulado 3D (Diseño para la Reparación):** Ubicar la electrónica de control (Arduino Uno, protoboard, batería 18650 y módulo TP4056) en la cámara superior seca de la carcasa de PLA (cerrada mediante tapa superior removible con pestaña, sin adhesivos permanentes), pasando los cables de los tres sensores hacia el faldón inferior a través de la ranura interna sellada.

### Precauciones

* ⚠️ **Impermeabilización y sellado de cámara superior:** Asegurar el cierre de la tapa superior removible y el sellado del paso de cables (reforzado con cinta americana resistente a la humedad) antes de sumergir el equipo para evitar cortocircuitos.
* ⚠️ **Despeje del orificio de ventilación lateral:** Verificar que el conducto de ventilación ubicado en la parte alta del faldón inferior no esté obstruido, permitiendo el escape del aire al sumergir el dispositivo y evitando burbujas estancadas sobre los sensores.

---

## Especificaciones Técnicas

* **Alimentación:** Batería recargable Li-ion 18650 (3,7 V) con módulo cargador TP4056 (5 V, 1 A) / Operación lógica a 5 V (puerto USB en modo depuración y transmisión IoT).
* **Consumo:** Bajo consumo energético optimizado para operación intermitente en terreno (encendido breve durante la medición, con disipación térmica pasiva sin rejillas).
* **Dimensiones:** 52 mm × 100 mm × 253 mm (largo × ancho × alto).
* **Peso carcasa PLA:** 197 g de filamento PLA (más peso de componentes electrónicos internos).
* **Costo total de materiales (BOM):** $40.876 CLP.

---

## Mapa de Conexiones (Pinout)

| Componente | Pin Arduino Uno | Función / Protocolo |
| :--- | :--- | :--- |
| **Sensor Temperatura (DS18B20)** | `D2` | Señal Digital 1-Wire (con resistencia pull-up de `4,7 kΩ`) |
| **Interruptor SPDT** | `D3` | Entrada Digital con resistencia interna (`INPUT_PULLUP`) |
| **LED Verde (Agua Apta)** | `D8` | Salida Digital (`HIGH` cuando cumple los 3 parámetros, con R de `220 Ω`) |
| **LED Rojo (Agua No Apta)** | `D9` | Salida Digital (`HIGH` si falla al menos 1 parámetro, con R de `220 Ω`) |
| **Sensor TDS V1.0** | `A0` | Lectura Analógica (Sólidos disueltos en ppm) |
| **Sensor Turbidez (TSW-20M)** | `A1` | Lectura Analógica (Nivel de turbidez en NTU) |

---

## Umbrales Operativos y Ecosistema IoT

El hardware está calibrado bajo los estándares operativos de las pastillas potabilizadoras **AquaTabs** y normativa **EPA / OMS**:

* **Temperatura mínima (> 10 °C):** Evita la ralentización severa de la desinfección química por frío.
* **Turbidez máxima (< 5 NTU):** Exigencia del fabricante de AquaTabs para evitar que partículas suspendidas escuden microorganismos.
* **Sólidos Disueltos Totales (< 500 ppm):** Estándar secundario (SMCL) de EPA/OMS para palatabilidad y dureza del agua.
* **Conectividad Cloud:** Al conectarse vía USB a un computador, un script en **Python** lee el puerto serial y transmite los registros en tiempo real al dashboard público en **ThingSpeak**: [Ver Canal ThingSpeak](https://thingspeak.mathworks.com/channels/3588837).

---

## Troubleshooting

| Problema | Posible Causa | Solución |
| :--- | :--- | :--- |
| Traspaso de agua hacia la electrónica superior | El agua asciende al sumergir el dispositivo debido a la presión hidrostática y al desplazamiento de volumen (principio de Arquímedes). | Asegurar el ajuste de la tapa superior removible y reforzar el sellado de la ranura interna de cables con cinta americana resistente a la humedad. |
| Lecturas erráticas o burbujas en los sensores | Aire atrapado dentro de la cámara inferior abierta al sumergir el equipo verticalmente. | Mantener despejado el orificio lateral de ventilación en el faldón inferior para permitir el escape del aire y el baño completo de los sensores. |
| Fluctuación o ruido en lecturas analógicas (`V_TDS`, `V_TURB`) | Variaciones instantáneas de voltaje en los conversores ADC. | Aplicar el filtro de estabilización en firmware (promedio móvil de 10 lecturas consecutivas por ciclo) y calibrar con muestras de control. |
