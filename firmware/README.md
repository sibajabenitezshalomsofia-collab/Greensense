# Firmware GreenSense

El archivo `greensense.ino` conserva la lógica compartida para el proyecto: lecturas del DHT11, humedad del suelo y sensor de lluvia; publicación en Blynk; y activación de la bomba cuando la humedad calculada del suelo es menor al 40 % y no se detecta lluvia.

## Configuración de credenciales
1. Copia `secrets.example.h` como `secrets.h` en esta carpeta.
2. Completa el archivo local `secrets.h` con tu Template ID, token de Blynk, nombre de Wi-Fi y contraseña.
3. No subas `secrets.h`: está excluido mediante el archivo raíz `.gitignore`.
4. Instala las bibliotecas Blynk y DHT y el soporte de placas ESP32 en Arduino IDE.
5. Selecciona la placa ESP32 Dev Module y el puerto correspondiente.

## Pines
- DHT11: GPIO 4
- Sensor de humedad del suelo: GPIO 34
- Sensor de lluvia: GPIO 35
- Relé de la bomba: GPIO 12

## Datastreams Blynk
- V1: temperatura
- V2: humedad del aire
- V3: humedad del suelo calculada
- V4: estado de bomba publicado por la lógica
- V5: lectura analógica del sensor de lluvia

## Notas de validación
- Calibración de suelo: seco = 2400, húmedo = 1200; son valores de referencia que deben coincidir con las lecturas reales del sensor.
- El umbral de lluvia es lectura analógica mayor que 800; verifica que corresponda al módulo que tienes.
- La lógica configura el relé en LOW para encender y cambia el pin a INPUT en la condición de apagado. INPUT deja el pin en alta impedancia y no garantiza que todos los módulos de relé queden apagados; valida el comportamiento de tu montaje antes de dejar la bomba conectada.
- La indicación en el Monitor Serie refleja la decisión del programa, no una medición eléctrica de que la bomba esté funcionando.
- Registra resultados reales en `docs/pruebas.md`. No se han añadido resultados de pruebas que no se hayan reportado.
