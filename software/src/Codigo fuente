// 1. IMPORTACIÓN DE LIBRERÍAS

#include "OneWire.h"
// Carga la librería base para habilitar la comunicación digital del sensor
#include "DallasTemperature.h"
// Carga la librería que traduce los datos del sensor de temperatura

// 2. Definición Pines

#define PIN_TEMPERATURA 2
#define PIN_TDS A0
#define PIN_TURBIDEZ A1
#define LED_VERDE 8
#define LED_ROJO 9

// 3. CREACIÓN DE OBJETOS (Configuración del sensor de temperatura)

OneWire oneWire(PIN_TEMPERATURA);
// Habilita el canal de comunicación del sensor en el pin asignado
DallasTemperature sensorTemp(&oneWire);
// Enlaza el sensor virtual con el canal de comunicación

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

  Serial.println("Sistema M.C.A. Fisico Iniciando...");
// Imprime este mensaje de bienvenida en la pantalla del computador.
}

// 5. BUCLE PRINCIPAL (El ciclo de trabajo que el Arduino repite sin parar mientras tenga batería)

void loop() {
  if (digitalRead(3) == LOW) {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_ROJO, LOW);
    return;
  }
// Verifica si el interruptor de seguridad está apagado. Si es así, apaga ambos LEDs y detiene el ciclo temporalmente sin medir nada.

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
// Calibracion agua limpia
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
  delay(1000);
// Realiza una pausa de 1 segundo (1000 milisegundos) antes de reiniciar todo el ciclo de medición.
}
