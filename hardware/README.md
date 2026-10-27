# Hardware y carcasa

Guarda aquí el esquema de conexiones, diagramas, archivos CAD/STL de la carcasa y notas de montaje.

## Conexiones conocidas
| Elemento | GPIO ESP32 | Nota |
|---|---:|---|
| DHT11 | 4 | Confirmar alimentación y tipo de módulo |
| Sensor de humedad del suelo | 34 | Entrada analógica |
| Sensor de lluvia/nivel de agua | 35 | Confirmar el modelo exacto |
| Módulo de relé | 12 | Verificar si el módulo es activo en LOW o HIGH |

Verifica el voltaje requerido por cada módulo y comparte una tierra común cuando el diseño lo requiera. No alimentes la bomba desde un GPIO. Mantén las conexiones aisladas del agua y evita cortocircuitos.
