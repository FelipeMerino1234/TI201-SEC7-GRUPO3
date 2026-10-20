# Testing y Validación

## Objetivo
Validar el funcionamiento del prototipo de monitoreo de calidad del agua, verificando que los sensores de temperatura, turbidez y sólidos disueltos funcionen correctamente y que el sistema entregue una respuesta mediante luces LED para indicar si el agua es apta o no para utilizar una pastilla potabilizadora.

---

## 📁 Carpetas

#### `reportes/`
Documentos con resultados del testing

#### `evidencias/`
Fotos y videos de sesiones con usuarios

#### `datos/`
Datos cuantitativos recolectados

---

## Metodología de Testing

### Grupo Objetivo
- **Perfil de usuarios:** Excursionistas y mochileros que realizan actividades de senderismo y trekking.
- **Cantidad mínima:** Indefinida
- **Ubicación:** Rutas de trekking y zonas de media y alta montaña de la Región Metropolitana, donde los usuarios necesitan abastecerse de agua desde fuentes naturales.

### Protocolo de Testing
1. **Briefing** (5 min)
   - Explicar propósito del prototipo
   - Contexto de uso

2. **Sesión de Uso** (15-20 min)
   - Usuario interactúa con prototipo
   - Observación sin intervención
   - Toma de notas

3. **Entrevista Post-Testing** (10 min)
   - Preguntas sobre experiencia
   - Feedback cualitativo
   - Sugerencias de mejora

4. **Encuesta Cuantitativa** (5 min)
   - Escala Likert (1-5)
   - Métricas específicas

---

## Métricas de Evaluación

### Usabilidad
- Facilidad de uso (1-5)
- Claridad de funcionamiento (1-5)
- Satisfacción general (1-5)

### Impacto ODS
-Evaluación de temperatura del agua.
-Evaluación de turbidez del agua.
-Evaluación de sólidos disueltos totales (TDS).
-Reducción de la incertidumbre al determinar si una fuente de agua cumple las condiciones necesarias para utilizar una pastilla potabilizadora.
### Desempeño Técnico
- Funcionamiento continuo sin interrupciones durante más de 5 minutos.
-Correcta respuesta de las luces LED frente a las mediciones de los sensores.
-Promedio de 10 mediciones consecutivas por sensor para estabilizar los datos y disminuir errores.

---

## Análisis de Resultados

### Cuantitativo
El prototipo evalúa tres parámetros:
- Temperatura: debe ser mayor a 10 °C.
- Turbidez: debe ser menor a 5 NTU.
- TDS: debe ser menor a 500 ppm.
Si las tres condiciones se cumplen simultáneamente, el sistema considera que el agua es apta para utilizar la pastilla potabilizadora. Si una de ellas falla, el agua se clasifica como no apta. Actividad Diseño 16-10-2026

### Cualitativo
- Durante el proceso de iteración se identificaron los siguientes aprendizajes:
- Fue necesario agregar fórmulas matemáticas al pasar desde el simulador Wokwi al Arduino físico.
- Los sensores de TDS y turbidez necesitaron calibración utilizando agua de la llave.
- Se identificó la necesidad de impermeabilizar la carcasa para proteger los componentes electrónicos del agua.

---

## Validación de Impacto ODS

**ODS Seleccionado:** ODS 6: Agua Limpia y Saneamiento / ODS 3 Salud y Bienestar.

**Meta específica del proyecto:** Entregar un diagnóstico previo en terreno que permita determinar si una fuente natural de agua reúne las condiciones mínimas necesarias para que una pastilla potabilizadora funcione correctamente. De manera complementaria, el proyecto se relaciona con el ODS 3: Salud y Bienestar, al buscar prevenir enfermedades gastrointestinales y cuadros de deshidratación.

**Indicadores de impacto:**
1. Turbidez — Límite establecido: menor a 5 NTU.
2. Temperatura — Límite establecido: mayor a 10 °C.
3. Sólidos Totales Disueltos — Límite establecido: menor a 500 ppm.

**Proyección de impacto a escala:**
El diseño puede replicarse en parques nacionales y podría ser entregado o validado por actores como CONAF y la Asociación Parque Cordillera para su utilización en senderos.
