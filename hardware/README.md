Hardware - Documentación

## Contenido

Esta carpeta contiene toda la documentación técnica del hardware del proyecto **Monitor de Calidad del Agua (Sistema E.V.A.)**.

### 📁 Carpetas

* `esquemas/`  
  Diagramas de circuitos y esquemáticos del sistema (conexiones físicas y simulación en Wokwi).

* `bom/`  
  Bill of Materials (Lista completa de materiales y componentes electrónicos).

* `fotos/`  
  Fotografías de alta resolución del prototipo ensamblado y pruebas en terreno/laboratorio.

---

## Instrucciones de Ensamble

### Componentes Principales

1. **Placa Arduino Uno** - Microcontrolador encargado de recibir las señales de los sensores, calcular el promedio móvil de 10 lecturas y controlar las alertas visuales.
2. **Sensor de Temperatura Sumergible (DS18B20)** - Mide la temperatura del agua en °C (conectado al pin digital `2` vía protocolo OneWire) para verificar que no ralentice el efecto químico de la pastilla potabilizadora.
3. **Sensor de Sólidos Disueltos Totales (TDS V1.0)** - Mide la concentración de sales, minerales y metales disueltos en ppm (conectado al pin analógico `A0`).
4. **Sensor de Turbidez Óptico (TSW-20M)** - Evalúa mediante un haz de luz la cantidad de partículas suspendidas en NTU (conectado al pin analógico `A1`).
5. **Indicadores LED (Verde y Rojo) y Resistencias** - Sistema de respuesta binaria inmediata: LED Verde (pin digital `8`) indica agua apta para pastilla y LED Rojo (pin digital `9`) alerta que al menos un parámetro está fuera de rango.
6. **Interruptor SPDT y Sistema de Alimentación (Batería 18650 + Módulo de Carga)** - Controla el encendido, pausa del sistema (pin digital `3` con `INPUT_PULLUP`) y provee energía autónoma en terreno.

### Pasos de Ensamblaje

1. **Montaje del circuito base:** Conectar la protoboard, las resistencias de protección y los LEDs (Verde al pin `8` y Rojo al pin `9`), junto con el interruptor SPDT al pin `3` y GND de la placa Arduino Uno.
2. **Conexión de sensores:** Conectar el sensor de temperatura DS18B20 al pin digital `2`, el sensor TDS al pin analógico `A0` y el sensor de turbidez TSW-20M al pin analógico `A1`, alimentándolos desde los rieles de 5 V y GND.
3. **Integración en el encapsulado 3D:** Ubicar la electrónica de control (Arduino Uno, protoboard, batería 18650 y módulo de carga) en la mitad superior hermética de la carcasa de PLA, pasando únicamente los cables de los tres sensores hacia la mitad inferior (faldón protector) a través de la ranura interna sellada.

### Precauciones

* ⚠️ **Impermeabilización de la sección superior:** Verificar que la tapa superior con sello de goma y la ranura interna de paso de cables estén completamente selladas antes de sumergir el equipo para evitar cortocircuitos en el Arduino o la batería.
* ⚠️ **Despeje del orificio de ventilación lateral:** Asegurarse de que el conducto de ventilación ubicado en la parte alta del faldón inferior no esté obstruido, permitiendo que escape el aire al sumergir el dispositivo y evitando burbujas estancadas sobre los sensores.

---

## Especificaciones Técnicas

* **Alimentación:** Batería recargable 18650 con módulo de carga / Operación lógica a 5 V (puerto USB 5 V en modo depuración).
* **Consumo:** Bajo consumo intermitente (operación breve solo durante los segundos de medición, con disipación térmica pasiva). *(Nota: Si midieron los mA exactos con tester, agrégalos aquí).*
* **Dimensiones:** 70 mm × 120 mm × 270 mm (7 cm de largo × 12 cm de ancho × 27 cm de alto).
* **Peso:** *(Completar con el peso exacto en gramos del prototipo ensamblado con batería).*

---

## Troubleshooting

| Problema | Posible Causa | Solución |
| :--- | :--- | :--- |
| El traspaso de agua hacia la electrónica superior | El agua sube al sumergir el dispositivo debido a la presión hidrostática y al desplazamiento de volumen (principio de Arquímedes). | Impermeabilizar la tapa superior con sello de goma y sellar la ranura interna por donde pasan los cables hacia los sensores. |
| Lecturas erráticas o con burbujas en los sensores | Aire atrapado dentro de la falda protectora inferior al sumergir el equipo verticalmente. | Mantener libre el orificio de ventilación lateral en la sección inferior para permitir el escape del aire y el baño completo de los sensores. |
| Fluctuación o ruido en los valores de TDS y Turbidez | Variaciones instantáneas de voltaje en las lecturas analógicas crudas (`V_TDS` y `V_TURB`). | Aplicar el filtro de estabilización en el código (promedio de 10 lecturas consecutivas por ciclo) y calibrar previamente con agua de la llave. |

## Umbrales Operativos y Calibración

El hardware está calibrado específicamente para validar la efectividad de pastillas potabilizadoras **AquaTabs**:

* **Temperatura mínima (> 10 °C):** Por debajo de este umbral, el frío ralentiza severamente la acción química del cloro (duplicando el tiempo de contacto necesario por cada 10 °C bajo los 15 °C), activando la alerta roja.
* **Turbidez máxima (< 5 NTU):** Exigencia oficial del fabricante de AquaTabs para evitar que partículas suspendidas protejan a los microorganismos de la desinfección.
* **Sólidos Disueltos Totales (< 500 ppm):** Basado en el estándar secundario (SMCL) de la EPA y la OMS para asegurar palatabilidad y evitar exceso de minerales o sabor salobre.


---
