import time
import requests
import serial

# --- CONFIGURACIÓN ---
PUERTO_ARDUINO = "PuertoCOM"
BAUDIOS = 9600
WRITE_API_KEY = "Insertar Acá Apikey del ThingSkeap"
URL_THINGSPEAK = "https://api.thingspeak.com/update"

print(f"Conectando a {PUERTO_ARDUINO}...")
arduino = serial.Serial(PUERTO_ARDUINO, BAUDIOS, timeout=3)
time.sleep(3)  # Espera a que el Arduino Uno termine de reiniciar

arduino.reset_input_buffer()  # Limpia lecturas en vivo previas
arduino.write(b"L")           # Solicita el volcado de la EEPROM
time.sleep(1.5)

subidos = 0
while True:
    linea = arduino.readline().decode("utf-8", errors="ignore").strip()
    if not linea:
        break

    print("Arduino dice:", linea)
    partes = linea.split(",")

    # Formato esperado: Muestra,Temp_C,TDS_ppm,Turbidez_NTU (4 columnas)
    if len(partes) == 4:
        try:
            muestra = int(partes[0])
            temp = float(partes[1])
            tds = float(partes[2])
            turb = float(partes[3])

            if temp > -100:
                payload = {
                    "api_key": WRITE_API_KEY,
                    "field1": temp,
                    "field2": tds,
                    "field3": turb,
                }
                resp = requests.get(URL_THINGSPEAK, params=payload, timeout=10)
                print(
                    f"--> Muestra #{muestra} subida a ThingSpeak | ID registro: {resp.text} "
                    f"(Temp={temp} C, TDS={tds} ppm, Turb={turb} NTU)"
                )
                subidos += 1
                time.sleep(16)  # Pausa obligatoria del plan gratuito de ThingSpeak
        except ValueError:
            pass  # Ignora la fila de encabezado o mensajes de texto

arduino.close()
print(f"Proceso terminado. Registros subidos: {subidos}")
