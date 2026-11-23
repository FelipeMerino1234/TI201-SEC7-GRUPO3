// 1. IMPORTACIÓN DE LIBRERÍAS

#include "OneWire.h"
// Carga la librería base para habilitar la comunicación digital del sensor
#include "DallasTemperature.h"
// Carga la librería que traduce los datos del sensor de temperatura
#include <EEPROM.h>
// Carga la librería para guardar datos en la memoria interna sin que se borren al apagar

// 2. Definición Pines

#define PIN_TEMPERATURA 2
#define PIN_TDS A0
#define PIN_TURBIDEZ A1
#define LED_VERDE 8
#define LED_ROJO 9

// 3. CREACIÓN DE OBJETOS Y VARIABLES DE MEMORIA

OneWire oneWire(PIN_TEMPERATURA);
// Habilita el canal de comunicación del sensor en el pin asignado
DallasTemperature sensorTemp(&oneWire);
// Enlaza el sensor virtual con el canal de comunicación

struct Medicion {
  float temp;
  float tds;
  float turbidez;
};
// Empaqueta los 3 datos de cada muestra en un solo bloque de 12 bytes

int totalGuardadas = 0;
const int MAX_MEDICIONES = 85;
// Límite seguro para los 1024 bytes de memoria EEPROM del Arduino Uno

bool yaGuardoMuestra = false;
int contadorEstabilizacion = 0;
// Controlan que se guarde solo 1 lectura estable por cada encendido del interruptor

// 4. CONFIGURACIÓN INICIAL (Bloque que se ejecuta una sola vez al encender el sistema)

void setup() {
  Serial.begin(9600);
  sensorTemp.begin();
  // Prende la comunicación con el compu a velocidad 9600 para ver los datos en pantalla.
  // Enciende el sensor de temperatura.

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
  // Le dice al Arduino que el enchufe del LED verde va a expulsar energía (salida) y que enchufe del LED rojo va a expulsar energía (salida).

  pinMode(3, INPUT_PULLUP);
  // Interruptor de seguridad: Configura el pin 3 como un botón de encendido/apagado interno.

  EEPROM.get(0, totalGuardadas);
  if (totalGuardadas < 0 || totalGuardadas > MAX_MEDICIONES) {
    totalGuardadas = 0;
  }
  // Recupera desde la memoria cuántas muestras hay guardadas de salidas anteriores.

  Serial.print("Sistema M.C.A. Fisico Iniciando... Muestras en memoria: ");
  Serial.println(totalGuardadas);
  // Imprime este mensaje de bienvenida en la pantalla del computador.
}

// 5. BUCLE PRINCIPAL (El ciclo de trabajo que el Arduino repite sin parar mientras tenga batería)

void loop() {
  revisarComandosPC();
  // Revisa si el computador envió 'L' (Leer) o 'B' (Borrar), incluso con el interruptor apagado.

  if (digitalRead(3) == LOW) {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_ROJO, LOW);
    yaGuardoMuestra = false;
    contadorEstabilizacion = 0;
    return;
  }
  // Verifica si el interruptor de seguridad está apagado. Si es así, apaga ambos LEDs, reinicia el estado de guardado y detiene el ciclo temporalmente.

  sensorTemp.requestTemperatures();
  float temperatura = sensorTemp.getTempCByIndex(0);
  // Le pide al sensor que lea la temperatura del agua y guarda ese valor numérico en la variable "temperatura".

  long sumaTDS = 0;
  long sumaTurbidez = 0;
  int muestras = 10;
  // Crea variables en cero para acumular las lecturas y define que el sistema tomará 10 muestras seguidas.

  for (int i = 0; i < muestras; i++) {
    sumaTDS += analogRead(PIN_TDS);
    sumaTurbidez += analogRead(PIN_TURBIDEZ);
    delay(5);
  }
  // Filtro de estabilización: Un ciclo rápido que lee los sensores 10 veces con una pausa de 5 milisegundos entre cada lectura, sumando los resultados.

  float lecturaTDS = sumaTDS / (float)muestras;
  float lecturaTurbidez = sumaTurbidez / (float)muestras;
  // Calcula el promedio exacto de las 10 lecturas para evitar que variaciones físicas del agua arrojen datos erráticos.

  float voltajeTDS = lecturaTDS * (5.0 / 1024.0);
  float voltajeTurbidez = lecturaTurbidez * (5.0 / 1024.0);
  voltajeTurbidez = voltajeTurbidez + 0.74;
  // Calibracion agua limpia (ajusta este valor si cambiaste el offset en tus pruebas)
  // Convierte la señal eléctrica bruta del Arduino (0 a 1023) en un valor de voltaje real (0 a 5V) y le aplica un ajuste manual de calibración al sensor de turbidez.

  float coeficienteCompensacion = 1.0 + 0.02 * (temperatura - 25.0);
  float voltajeCompensado = voltajeTDS / coeficienteCompensacion;
  float tdsPPM = (133.42 * pow(voltajeCompensado, 3) - 255.86 * pow(voltajeCompensado, 2) + 857.39 * voltajeCompensado) * 0.5;
  // Compensa el valor del TDS basándose en la temperatura (ya que el frío o calor alteran la conductividad) y aplica la fórmula polinómica para convertir el voltaje a partes por millón (ppm).

  float turbidezNTU = 0;
  if (voltajeTurbidez < 2.5) {
    turbidezNTU = 3000;
  } else {
    turbidezNTU = -1120.4 * (voltajeTurbidez * voltajeTurbidez) + 5742.3 * voltajeTurbidez - 4353.8;
  }
  // Transforma el voltaje de la turbidez a unidades estándar (NTU) utilizando la ecuación cuadrática recomendada por el fabricante del sensor. Si el voltaje cae mucho, asume turbidez máxima (3000).

  if (turbidezNTU < 0) {
    turbidezNTU = 0;
  }
  // Medida de seguridad y limpieza de datos: Si la fórmula arroja un número negativo (físicamente imposible), lo fuerza a 0.

  // NUEVA TELEMETRÍA: Extracción de Voltajes Crudos
  Serial.print("V_TDS: ");
  Serial.print(voltajeTDS, 2);
  Serial.print("V | V_TURB: ");
  Serial.print(voltajeTurbidez, 2);
  Serial.print("V | Temp: ");
  Serial.print(temperatura);
  Serial.print(" C | TDS: ");
  Serial.print(tdsPPM);
  Serial.print(" ppm | Turbidez: ");
  Serial.print(turbidezNTU);
  Serial.println(" NTU");
  // Imprime en el monitor de la computadora todos los voltajes y resultados finales calculados para que el equipo evalúe las pruebas de laboratorio en tiempo real.

  if (temperatura <= 10.0 || turbidezNTU >= 5.0 || tdsPPM >= 500) {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_ROJO, HIGH);
  } else {
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_ROJO, LOW);
  }
  // Lógica de decisión principal: Si la temperatura es muy fría para la pastilla (<=10), la turbidez es muy alta (>=5) o los sólidos son excesivos (>=500), enciende el LED Rojo (peligro). Si todos los parámetros cumplen, enciende el LED Verde (seguro).

  // GUARDADO AUTOMÁTICO EN EEPROM TRAS ESTABILIZACIÓN
  if (!yaGuardoMuestra) {
    contadorEstabilizacion++;
    if (contadorEstabilizacion >= 5) {
      guardarMedicion(temperatura, tdsPPM, turbidezNTU);
      yaGuardoMuestra = true;
    }
  }
  // Espera 5 ciclos (5 segundos) desde que se encendió el interruptor para que los sensores se estabilicen y guarda 1 registro permanente.

  delay(1000);
  // Realiza una pausa de 1 segundo (1000 milisegundos) antes de reiniciar todo el ciclo de medición.
}

// 6. FUNCIONES DE MEMORIA EEPROM (Guardar, Leer y Borrar)

void guardarMedicion(float t, float tds, float turb) {
  if (totalGuardadas < MAX_MEDICIONES) {
    Medicion nueva = {t, tds, turb};
    int direccion = 2 + (totalGuardadas * sizeof(Medicion));
    EEPROM.put(direccion, nueva);
    totalGuardadas++;
    EEPROM.put(0, totalGuardadas);
    Serial.print(">> [EEPROM] Muestra #");
    Serial.print(totalGuardadas);
    Serial.println(" guardada correctamente.");
  } else {
    Serial.println(">> [EEPROM] Memoria llena (85 muestras). Descarga y borra los datos.");
  }
}

void revisarComandosPC() {
  if (Serial.available() > 0) {
    char comando = Serial.read();
    if (comando == 'L' || comando == 'l') {
      Serial.println("Muestra,Temp_C,TDS_ppm,Turbidez_NTU");
      for (int i = 0; i < totalGuardadas; i++) {
        Medicion m;
        int direccion = 2 + (i * sizeof(Medicion));
        EEPROM.get(direccion, m);
        Serial.print(i + 1); Serial.print(",");
        Serial.print(m.temp); Serial.print(",");
        Serial.print(m.tds); Serial.print(",");
        Serial.println(m.turbidez);
      }
    } else if (comando == 'B' || comando == 'b') {
      totalGuardadas = 0;
      EEPROM.put(0, totalGuardadas);
      Serial.println(">> [EEPROM] Memoria borrada y lista para la proxima salida.");
    }
  }
}
