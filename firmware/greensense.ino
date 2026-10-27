/*
 * Proyecto: GreenSense - Sistema IoT de Riego Inteligente
 * Institución Educativa Colegio Jorge Gaitán Cortés
 * Autores: S. S. Sibaja, G. A. Torres, S. Solano, J. E. Mantilla
 * Asesor: Diego Bautista Pulido
 * Año: 2026
 *
 * Versión publicada sin credenciales privadas.
 * Configura firmware/secrets.h en tu equipo; nunca lo subas a GitHub.
 */

#include "secrets.h"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

/* Configuración de Pines del ESP32 */
#define DHTPIN 4
#define DHTTYPE DHT11
#define SOIL_PIN 34
#define RAIN_PIN 35
#define RELAY_PIN 12

/* Variables para Calibración del Sensor de Suelo */
int valorSeco = 2400;
int valorHumedo = 1200;

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

// Lee los sensores y controla la bomba según la humedad del suelo y la lluvia.
void enviarSensores() {
  // 1. Leer humedad y temperatura del aire
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  // 2. Leer humedad del suelo y convertir a porcentaje
  int lecturaSuelo = analogRead(SOIL_PIN);
  int porcentajeSuelo = map(lecturaSuelo, valorSeco, valorHumedo, 0, 100);
  porcentajeSuelo = constrain(porcentajeSuelo, 0, 100);

  // 3. Leer sensor de lluvia analógico
  int lecturaLluvia = analogRead(RAIN_PIN);

  // En la configuración usada por el proyecto: mayor a 800 significa agua/lluvia.
  // Este umbral depende del sensor y debe comprobarse con lecturas reales.
  bool estaLloviendo = (lecturaLluvia > 800);

  // 4. Lógica de riego: regar si el suelo está por debajo del 40 % y no llueve.
  bool bombaEncendida = false;

  if (porcentajeSuelo < 40 && !estaLloviendo) {
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW);
    Blynk.virtualWrite(V4, 1);
    bombaEncendida = true;
  } else {
    // Se conserva la lógica de la versión del proyecto.
    // INPUT deja el pin en alta impedancia; verifica el comportamiento real
    // del módulo de relé antes de confiar en que la bomba queda apagada.
    pinMode(RELAY_PIN, INPUT);
    Blynk.virtualWrite(V4, 0);
    bombaEncendida = false;
  }

  // Diagnóstico en el Monitor Serie
  Serial.print("Suelo: ");
  Serial.print(porcentajeSuelo);
  Serial.print("% | Lluvia: ");
  Serial.print(lecturaLluvia);
  Serial.print(" | ¿Bomba ON?: ");
  Serial.println(bombaEncendida ? "SI (según la lógica)" : "NO (según la lógica)");
  Serial.println("------------------------------------");

  // 5. Enviar datos a Blynk
  if (!isnan(t) && !isnan(h)) {
    Blynk.virtualWrite(V1, t);  // V1: Temperatura
    Blynk.virtualWrite(V2, h);  // V2: Humedad del aire
  } else {
    Serial.println("Error al leer el sensor DHT.");
  }

  Blynk.virtualWrite(V3, porcentajeSuelo); // V3: Humedad del suelo
  Blynk.virtualWrite(V5, lecturaLluvia);   // V5: Lectura del sensor de lluvia
}

void setup() {
  Serial.begin(115200);

  // Inicializar el pin del relé como entrada, según la versión del proyecto.
  pinMode(RELAY_PIN, INPUT);
  pinMode(RAIN_PIN, INPUT);

  dht.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Ejecutar la función cada 2 segundos
  timer.setInterval(2000L, enviarSensores);
}

void loop() {
  Blynk.run();
  timer.run();
}
