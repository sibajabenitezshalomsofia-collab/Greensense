# GreenSense 🌱

Sistema de riego inteligente basado en ESP32 para observar las condiciones de una planta y apoyar el riego según la humedad del suelo y la detección de lluvia.

## Objetivo
Construir un prototipo que mida variables ambientales y del suelo, y permita supervisar las lecturas mediante Blynk IoT. El control de la bomba debe comprobarse durante las pruebas integradas antes de afirmar que funciona correctamente.

## Componentes principales
- ESP32 DevKit V1
- Sensor de humedad y temperatura DHT11
- Sensor de humedad del suelo
- Sensor de lluvia o nivel de agua (confirmar modelo exacto)
- Módulo de relé de un canal
- Bomba de agua pequeña, manguera y recipiente
- Protoboard y cables Dupont
- Fuente USB/power bank compatible
- Carcasa impresa en 3D

## Asignación de pines documentada en el código actual
| Componente | Pin ESP32 |
|---|---|
| DHT11 | GPIO 4 |
| Humedad del suelo (salida analógica) | GPIO 34 |
| Sensor de lluvia (salida analógica) | GPIO 35 |
| Señal del relé | GPIO 12 |

Comprueba este cuadro frente al montaje físico antes de conectar la alimentación. No conectes la bomba directamente a un pin del ESP32.

## Arquitectura
Sensores → ESP32 → procesamiento de lecturas → panel Blynk IoT.  
El ESP32 controla el módulo de relé para accionar la bomba según la lógica programada, siempre que esa función haya sido validada con pruebas.

## Estructura del repositorio
- `firmware/`: código del ESP32 y notas de compilación.
- `hardware/`: conexiones, esquema y archivos de la carcasa.
- `docs/`: informe, resultados de pruebas y documentación.
- `images/`: fotografías del prototipo y diagramas.

## Preparación
1. Abre `firmware/README.md` y consulta las bibliotecas necesarias.
2. Abre el archivo del firmware en Arduino IDE.
3. Instala las bibliotecas que use el programa (por ejemplo, la biblioteca DHT y la biblioteca de Blynk).
4. Configura las credenciales localmente, sin subirlas al repositorio.
5. Selecciona la placa ESP32 Dev Module, el puerto correcto y compila.
6. Sube el programa y prueba cada sensor por separado antes de hacer la prueba integrada.

## Seguridad y privacidad
**No publiques tokens de Blynk, contraseñas Wi-Fi ni otros secretos.** Usa marcadores de posición en ejemplos públicos y configura tus credenciales localmente. Si alguna credencial real se publicó anteriormente, cámbiala.

## Estado de las pruebas
Los resultados deben registrarse después de probar físicamente el prototipo. No se declaran mediciones ni funcionamiento automático sin evidencia.

## Autoría
Proyecto escolar GreenSense — Colegio Jorge Gaitán Cortés I.E.D.  
Integrantes, curso, docente y fecha de entrega: completar con los datos reales.
