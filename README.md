# GreenSense 🌱

Sistema IoT de riego inteligente basado en ESP32 para observar las condiciones de una planta y controlar una bomba según la humedad del suelo y la detección de lluvia.

## Objetivo
El prototipo lee temperatura y humedad ambiental con un DHT11, estima la humedad del suelo, lee un sensor de lluvia y envía datos a Blynk IoT. La lógica compartida en el firmware activa la bomba cuando la humedad del suelo calculada es inferior al 40 % y no se detecta lluvia.

## Componentes principales
- ESP32 DevKit V1
- Sensor DHT11
- Sensor capacitivo de humedad del suelo
- Sensor analógico de lluvia
- Módulo de relé de un canal
- Bomba pequeña, manguera y recipiente
- Protoboard y cables Dupont
- Fuente USB/power bank compatible
- Carcasa impresa en 3D

## Pines del firmware
| Componente | GPIO ESP32 |
|---|---:|
| DHT11 | 4 |
| Humedad del suelo (analógico) | 34 |
| Sensor de lluvia (analógico) | 35 |
| Relé de la bomba | 12 |

## Datastreams de Blynk
| Pin virtual | Dato |
|---|---|
| V1 | Temperatura |
| V2 | Humedad ambiental |
| V3 | Humedad del suelo calculada |
| V4 | Estado de bomba indicado por la lógica |
| V5 | Lectura analógica del sensor de lluvia |

## Estructura
- `firmware/`: código e instrucciones de configuración.
- `hardware/`: conexiones y archivos de la carcasa.
- `docs/`: documentación y registro de pruebas.
- `images/`: fotografías y diagramas.

## Configuración
Consulta `firmware/README.md`. Las credenciales se guardan localmente en `firmware/secrets.h`, excluido por `.gitignore`. Nunca publiques tokens de Blynk ni contraseñas Wi-Fi.

## Pruebas
Los resultados se deben registrar después de probar físicamente el prototipo. El estado indicado por el programa no sustituye la comprobación real de la bomba.

## Autoría
Colegio Jorge Gaitán Cortés — 2026.  
Autores declarados en el firmware: S. S. Sibaja, G. A. Torres, S. Solano y J. E. Mantilla.  
Asesor: Diego Bautista Pulido.
