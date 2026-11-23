# Archivos Fusion 360

## Archivos Requeridos

### `modelo_completo_v3.f3d`
Archivo principal con **historial de cambios completo**

**DEBE INCLUIR:**
-  Todos los componentes modelados
-  Ensamble completo funcional
-  Historial de diseño (timeline)
-  Materiales asignados
-  Constraints y relaciones

---

## Estructura del Modelo

### Componentes (Components)
```
Ensamble_Principal
├── Encapsulado_Inferior
├── Encapsulado_Superior
├── ESP32_DevKit
├── Sensor_DHT22
├── LED_Indicador
├── Soporte_Bateria
├── Bracket_Montaje
└── Tornilleria
```

### Uniones (Joints)
Documentar las juntas principales y sus restricciones

### Parámetros
Listar parámetros principales utilizados:
- `ancho_total = 120mm`
- `alto_total = 80mm`
- `grosor_pared = 2mm`

---

## Instrucciones de Apertura

1. Abrir Fusion 360
2. File > Open > Seleccionar archivo `.f3d`
3. Verificar que todas las referencias están cargadas
4. Revisar timeline para ver historial

---

## Versiones

| Versión | Fecha | Cambios Principales |
|---------|-------|---------------------|
| v3.0 | [Fecha] | Versión final retroalimentada Avance #3 |
| v2.1 | [Fecha] | Avance #2 |
| v1.0 | 29/08/26 | Dibujo Referencial |

---
