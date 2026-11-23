# Código fuente — Monitor de Calidad del Agua (M.C.A.)


Alcance: el sistema verifica tres **umbrales definidos en el prototipo**, pero **no certifica que el agua sea potable**, no detecta microorganismos y no demuestra por sí solo la eficacia de las pastillas potabilizadoras. Deben seguirse las instrucciones del fabricante y los procedimientos sanitarios aplicables.

## 1. Archivos de esta carpeta

| Archivo | Función | Estado |
|---|---|---|
| [`Codigo_Arduino_V3.ino`](Codigo_Arduino_V3.ino) | Firmware principal del Arduino Uno: sensores, cálculos, LEDs, comunicación serial y EEPROM. | Disponible |
| [`subir_código.py`](subir_código.py) | Programa Python que solicita al Arduino las mediciones guardadas en EEPROM y las transmite al canal ThingSpeak. | Disponible; **requiere corregir exposición de clave de API y puerto COM** |
| [`Codigo_Arduino_V2.ipynb`](Codigo_Arduino_V2.ipynb) | Registro de una versión anterior del código Arduino, conservado como evidencia de iteración. | Disponible; contiene código C/C++ en una libreta con kernel Python y **no se ejecuta como notebook Python** |
| `README.md` | Explicación técnica, instalación, uso, resultados, limitaciones y pendientes. | Este documento |

La versión **V3** es la que se documenta como firmware vigente. El nombre `main.ino` utilizado en documentación previa **no corresponde al archivo actual de esta carpeta**. Del mismo modo, el gateway subido se llama `subir_código.py`, **no** `subir_eva.py` ni `gateway_thingspeak.py`. Las capturas experimentales proporcionadas por el equipo muestran la ejecución de un archivo llamado `subir_eva.py`; **FALTA** establecer si corresponde exactamente a la misma versión que `subir_código.py`.

## 2. Arquitectura y funcionamiento

```text
DS18B20 (temperatura, D2) ─────────┐
TDS V1.0 (sólidos disueltos, A0) ──┼──> Arduino Uno ──> LED verde / LED rojo
TSW-20M (turbidez, A1) ────────────┘         |
                                              v
                                      EEPROM (hasta 85 registros)
                                              |
                                 Comando «L» por USB / 9600 baudios
                                              |
                                       PC con Python 3
                                              |
                                    HTTP → ThingSpeak
                                    (campos 1, 2 y 3)
```

El dispositivo realiza la medición y el control de LEDs localmente. **No requiere Internet para calcular las lecturas o ejecutar su lógica de alertas.** Para subir el historial a ThingSpeak sí se necesita conectar el Arduino por USB a un computador que ejecute el script Python y tenga conexión a Internet.

El código Python existente **consulta los registros de EEPROM cuando se ejecuta**; no mantiene una transferencia automática continua de todas las lecturas en vivo mientras el equipo está en terreno.

## 3. Hardware y asignación de pines

| Elemento | Pin Arduino Uno | Operación |
|---|---|---|
| Sensor de temperatura DS18B20 | `D2` | Comunicación digital 1-Wire; conexión de datos con resistencia pull-up de 4,7 kΩ según documentación del hardware |
| Interruptor SPDT | `D3` | Entrada `INPUT_PULLUP`: con lectura `LOW` se detiene la medición y se apagan los LEDs |
| Sensor TDS V1.0 | `A0` | Lectura analógica |
| Sensor de turbidez TSW-20M | `A1` | Lectura analógica |
| LED verde | `D8` | Se enciende cuando se cumplen simultáneamente los tres umbrales |
| LED rojo | `D9` | Se enciende cuando al menos uno de los tres umbrales no se cumple o falla la lectura de temperatura |

Según los informes, cada LED tiene una resistencia limitadora de **220 Ω**. El programa usa **9600 baudios** para el puerto serial.

## 4. Descripción del firmware `Codigo_Arduino_V3.ino`

### 4.1 Librerías y configuración inicial: `setup()`

El firmware incluye `OneWire.h`, `DallasTemperature.h` y `EEPROM.h`. Al iniciarse:

1. Abre el puerto serial a 9600 baudios.
2. Inicializa el DS18B20 a través de OneWire.
3. Configura `D8` y `D9` como salidas para los LEDs y `D3` como entrada con pull-up interno.
4. Recupera de la EEPROM el contador de muestras almacenadas. Si está fuera del intervalo válido, lo reinicia a cero.
5. Muestra un mensaje de inicio y el número de registros guardados.

### 4.2 Ciclo de medición: `loop()`

El programa comprueba primero si hay comandos seriales (`L` o `B`). A continuación:

1. **Interruptor:** si `D3` está en `LOW`, apaga ambos LEDs, reinicia el contador de estabilización y no ejecuta una medición en ese ciclo.
2. **Temperatura:** solicita **una lectura por ciclo** al DS18B20. Si recibe el valor de desconexión o una temperatura menor o igual a −55 °C, comunica el error, apaga el LED verde y enciende el rojo.
3. **Señales analógicas:** toma **10 lecturas de TDS y 10 de turbidez**, separadas por pausas de 5 ms, y calcula el promedio de cada grupo.
4. **Conversión de valores:** transforma las lecturas analógicas a voltios y aplica las expresiones y compensaciones incluidas en el firmware para expresar los resultados en ppm y NTU.
5. **Evaluación:** compara temperatura, TDS y turbidez con los umbrales de la sección siguiente y activa el LED correspondiente.
6. **Telemetría:** imprime por serial voltajes y lecturas físicas, lo que permite inspeccionarlas con Arduino IDE.
7. **EEPROM:** guarda **un registro por activación del interruptor**, después de contar cinco ciclos válidos de medición; no guarda repetidamente cada ciclo mientras permanece en ese estado.
8. Ejecuta una pausa de `delay(1000)` antes del ciclo siguiente.

**Precisión de la descripción temporal:** los cinco ciclos de estabilización **no equivalen necesariamente a cinco segundos exactos**, porque la conversión del sensor de temperatura y las demás operaciones también consumen tiempo. El período total del ciclo tampoco es exactamente de un segundo.

### 4.3 Cálculos de sensores

**TDS:** se convierte la señal analógica `A0` a voltios suponiendo una referencia ADC de **5,0 V**. El programa compensa el voltaje por temperatura respecto de 25 °C mediante el factor `1 + 0,02 × (temperatura − 25)`, y aplica una expresión polinómica cúbica para obtener ppm.

**Turbidez:** se convierte `A1` a voltios y se suma un ajuste implementado de **+0,74 V**. Para voltajes compensados inferiores a 2,5 V el código asigna 3000 NTU; en los demás casos utiliza una expresión cuadrática y limita a cero los resultados negativos.

Esos ajustes son **los valores codificados**. **FALTA** adjuntar una calibración metrológica independiente, con patrones de referencia e incertidumbre, que demuestre la exactitud de las lecturas en ppm y NTU.

### 4.4 Regla de decisión y LEDs

| Variable | Condición para LED verde | Condición que activa LED rojo |
|---|---|---|
| Temperatura | `T > 10 °C` | `T ≤ 10 °C` |
| TDS | `TDS < 500 ppm` | `TDS ≥ 500 ppm` |
| Turbidez | `NTU < 5` | `NTU ≥ 5` |

**LED verde:** sólo cuando las tres condiciones de la columna central se cumplen a la vez.  
**LED rojo:** cuando falla cualquiera de ellas, o cuando el firmware detecta un error de lectura del DS18B20.

Los valores son **criterios operativos del proyecto**, documentados en los informes. El límite de TDS de 500 ppm no es una verificación directa de la eficacia desinfectante de las pastillas y una señal verde **no implica agua segura para consumo humano**.

### 4.5 Memoria EEPROM y comandos seriales

El firmware define una estructura `Medicion` con tres valores `float` (temperatura, TDS y turbidez) y un máximo de **85 registros**. En la plataforma Arduino Uno, cada estructura ocupa 12 bytes y el contador se guarda al comienzo de la EEPROM. Los registros permanecen almacenados al cortar la alimentación, salvo que sean borrados o sobrescritos mediante operaciones posteriores.

| Comando enviado por Monitor Serial | Comportamiento programado |
|---|---|
| `L` o `l` | Lista los registros de EEPROM en líneas CSV, con encabezado `Muestra,Temp_C,TDS_ppm,Turbidez_NTU` |
| `B` o `b` | Reinicia a cero el contador de registros; no realiza un borrado físico seguro de todos los bytes de EEPROM |

Al alcanzar 85 muestras, el firmware indica que la memoria está llena. Se recomienda recuperar y respaldar los datos antes de enviar `B`.

## 5. Programa Python `subir_código.py` y ThingSpeak

El programa utiliza los paquetes `pyserial` y `requests`. Su funcionamiento **según el archivo actualmente subido** es:

1. Abre el puerto definido en `PUERTO_ARDUINO` (**`COM5`** en la versión existente) a **9600 baudios**.
2. Espera tres segundos después de establecer la conexión USB, limpia el búfer de entrada y transmite el carácter `L` al Arduino.
3. Lee las líneas CSV de los registros guardados en la EEPROM. Sólo procesa las que contienen cuatro campos convertibles a índice de muestra, temperatura, TDS y turbidez.
4. Envía una solicitud HTTP a la API de ThingSpeak, con temperatura en `field1`, TDS en `field2` y turbidez en `field3`.
5. Introduce una pausa de **16 segundos entre registros enviados** para respetar el intervalo configurado en esta versión.
6. Cierra la conexión serial e imprime el contador de registros procesados.

**Canal público informado en el Avance 3:** https://thingspeak.mathworks.com/channels/3588837

**Limitaciones verificadas en el código actual:**

- El script carga registros **históricos de EEPROM**, no todas las lecturas en vivo. Tampoco borra automáticamente los registros una vez transmitidos; si se ejecuta de nuevo, **puede volver a enviar los mismos**.
- Se envían únicamente los campos `field1`, `field2` y `field3`. El script actual **no transmite por separado un estado de LED** ni ejecuta una función específica de cálculo de aptitud; cualquier indicador virtual del panel debe configurarse por otro mecanismo que **FALTA** documentar.
- La consola puede contar una carga como realizada sin verificar de manera suficiente si ThingSpeak aceptó el registro; **FALTA** una comprobación robusta del estado HTTP y del ID devuelto (en ThingSpeak, una respuesta `0` indica normalmente que no se creó un registro).
- **FALTA** corroborar si `subir_código.py` es idéntico al programa `subir_eva.py` mencionado en las capturas experimentales.

### Seguridad de la clave API — corrección necesaria

La versión de `subir_código.py` revisada contiene una **clave de escritura de ThingSpeak incrustada directamente en el código**. Como el repositorio es público, **se debe regenerar esa clave en ThingSpeak** y cambiar el programa para obtenerla desde una variable de entorno o desde una configuración local excluida del control de versiones. No se reproduce la clave en este documento. **FALTA** aplicar y verificar esta corrección en el código fuente. Eliminar la clave del archivo sin regenerarla no corrige su exposición anterior en el historial de GitHub.

## 6. Instalación y ejecución

### 6.1 Arduino

**Requisitos:** Arduino Uno, cable USB de datos, Arduino IDE y librerías **OneWire** y **DallasTemperature**. `EEPROM.h` forma parte del entorno Arduino AVR.

1. Instalar las librerías desde el gestor de librerías de Arduino IDE.
2. Abrir [`Codigo_Arduino_V3.ino`](Codigo_Arduino_V3.ino) en Arduino IDE y, si lo solicita, permitir que se cree la carpeta del sketch con el mismo nombre.
3. Seleccionar **Arduino Uno** y el puerto USB correspondiente.
4. Verificar/compilar y cargar el firmware a la placa.
5. Para observar lecturas, abrir el **Monitor Serial a 9600 baudios**.



### 6.2 Python y envío de registros

Instalar dependencias en el computador:

```bash
python -m pip install pyserial requests
```

Antes de ejecutar, revisar en el archivo `subir_código.py` el puerto serial y **corregir la gestión de la API key y puerto COM** descrita arriba. Cerrar el Monitor Serial de Arduino IDE para liberar el puerto. En Windows, desde la carpeta `software/src/`, la instrucción usada es:

```bash
python "subir_código.py"
```

El programa solicita el historial mediante `L` y trata de enviarlo a ThingSpeak. **No iniciar la carga con una clave expuesta o revocada.** La ejecución requiere una clave válida configurada de forma segura y acceso a Internet.


