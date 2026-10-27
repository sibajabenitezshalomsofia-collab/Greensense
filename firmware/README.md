# Firmware GreenSense

Aquí debe guardarse el sketch probado del ESP32 (por ejemplo, `greensense.ino`).

## Configuración
- Placa: ESP32 DevKit V1 / ESP32 Dev Module.
- Pines documentados: DHT11 GPIO 4; humedad del suelo GPIO 34; sensor de lluvia GPIO 35; relé GPIO 12. Confirma que coincidan con el montaje real.
- Bibliotecas: instala las que aparezcan en los `#include` del sketch, como DHT y Blynk si corresponden.

## Antes de subir el código
1. Borra cualquier token real de Blynk y contraseña Wi-Fi del archivo.
2. Coloca las credenciales localmente o en un archivo privado que no se suba a GitHub.
3. Compila y prueba primero cada sensor por separado.
4. Comprueba el comportamiento del relé sin conectar la bomba; después prueba el sistema con supervisión.

No afirmes que la bomba funciona automáticamente hasta completar una prueba integrada y registrarla en `docs/pruebas.md`.
