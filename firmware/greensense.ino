/*
 * GreenSense — firmware ESP32
 * Publicado sin credenciales reales.
 *
 * Antes de compilar:
 * 1. Copia secrets.example.h como secrets.h dentro de esta carpeta.
 * 2. Rellena secrets.h con tus credenciales reales SOLO en tu equipo.
 * 3. No subas secrets.h a GitHub.
 */

#include "secrets.h"  // Archivo local ignorado por Git; contiene credenciales privadas.

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// --- Definición de pines ---
#define DHTPIN 4
#define DHTTYPE DHT11

#define SOIL_PIN 34
#define RAIN_PIN 35
#define RELAY_PIN 26

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

// Envía las lecturas de los sensores a Blynk cada 2 segundos.
void sendSensorData() {
  // Temperatura y humedad ambiental
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (!isnan(h) && !isnan(t)) {
    Blynk.virtualWrite(V0, t);  // Temperatura (°C)
    Blynk.virtualWrite(V1, h);  // Humedad ambiental (%)
  } else {
    Serial.println("Error al leer el sensor DHT.");
  }

  // Humedad del suelo: calibración aproximada, verificar en el montaje real.
  int soilVal = analogRead(SOIL_PIN);
  int soilPercent = map(soilVal, 3500, 1500, 0, 100);
  soilPercent = constrain(soilPercent, 0, 100);
  Blynk.virtualWrite(V2, soilPercent);

  // Sensor analógico de lluvia: porcentaje relativo, no probabilidad meteorológica.
  int rainVal = analogRead(RAIN_PIN);
  int rainPercent = map(rainVal, 4095, 1000, 0, 100);
  rainPercent = constrain(rainPercent, 0, 100);
  Blynk.virtualWrite(V3, rainPercent);
}

// Control manual de la bomba desde Blynk (datastream virtual V4).
// Este código supone un relé activo en HIGH. Verifica el módulo real antes
// de conectar la bomba: un relé activo en LOW requiere invertir esta lógica.
BLYNK_WRITE(V4) {
  int relayState = param.asInt();
  digitalWrite(RELAY_PIN, relayState ? HIGH : LOW);
}

void setup() {
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);  // Nivel inicial; no garantiza apagado en todos los relés.

  dht.begin();

  // Blynk.begin puede bloquear la ejecución mientras intenta conectarse.
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(2000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}
