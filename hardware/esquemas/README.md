# Esquemas de Circuito

## Archivos Requeridos

### Formato EasyEDA (Esquemático Oficial - Avance #3)
* `esquematico.pdf` - Exportación oficial en PDF del esquemático electrónico elaborado en EasyEDA (Proyecto_EVA, V1.0)
* `esquematico_easyeda.png` - Captura de alta resolución del diagrama de conexiones y asignación de pines
* `esquematico_easyeda.json` - Archivo fuente del proyecto en EasyEDA para edición o replicación

### Formato Wokwi (Simulación Inicial - Avance #1 y #2)
* `wokwi_diagram.json` - Archivo de configuración de componentes y conexiones de la simulación en Wokwi (`M.C.A`)
* `wokwi_screenshot.png` - Captura del circuito simulado con potenciómetros, sensor DS18B20, interruptor y LEDs
* `wokwi_link.txt` - URL del proyecto de simulación en línea en Wokwi

---

## Nomenclatura de Archivos

* Usar nombres descriptivos según la herramienta y etapa del proyecto.
* Incluir versión: `v3_esquema_final.pdf` (EasyEDA) / `v1_simulacion_wokwi.json` (Wokwi).
* Fecha en formato: `20261119_esquematico_easyeda.pdf`.

---

## Notas de Diseño

* **Compatibilidad eléctrica a 5 V y alimentación autónoma:** Todo el sistema opera bajo una línea regulada de 5 V y tierra común (GND) alimentada por una batería recargable Li-ion 18650 (3,7 V) conectada a través de un módulo cargador/elevador TP4056 (5 V, 1 A), permitiendo operación independiente en terreno sin depender de conexión USB.
* **Protección de componentes y estabilidad de señales:**
  * Se incorporó una resistencia pull-up de `4,7 kΩ` entre la línea de 5 V y el pin de datos (`D2`) del sensor digital de temperatura DS18B20 para garantizar la estabilidad de la comunicación bajo protocolo 1-Wire.
  * Se añadieron dos resistencias limitadoras de corriente de `220 Ω` en serie con los diodos LED Verde (`D8`) y Rojo (`D9`) para proteger las salidas digitales del microcontrolador ATmega328P.
* **Control de encendido mediante Pull-Up interno:** El interruptor deslizante SPDT se conectó directamente entre el pin digital `D3` y tierra (GND), aprovechando la resistencia interna `INPUT_PULLUP` del Arduino Uno para reducir componentes externos y simplificar el cableado.
* **Lectura analógica directa:** Los módulos de sólidos disueltos (TDS V1.0 en `A0`) y turbidez óptica (TSW-20M en `A1`) entregan salidas analógicas compatibles directamente con el conversor ADC de 10 bits del Arduino Uno, evitando etapas adicionales de acondicionamiento de señal.
* **Diseño para la reparación:** El circuito se implementó sobre una protoboard de 400 puntos con conectores desmontables y cables Dupont (jumpers) en lugar de soldaduras permanentes, facilitando el diagnóstico y reemplazo rápido de cualquier sensor dañado en campo.
