# Razonamiento Detallado de la Solución: Fotocopiadora Rebelde

## 1. Análisis de Requisitos Clave

Identifiqué cuatro requisitos fundamentales:

1. **Exclusión mutua**  
   - *Problema*: La fotocopiadora es un recurso no compartible  
   - *Solución necesaria*: Mecanismo que garantice acceso único

2. **Restricción de enfriamiento**  
   - *Regla*: 2 trabajos B consecutivos → 5s de cooldown obligatorio  
   - *Reto*: Detectar secuencias sin afectar concurrencia

3. **Prioridad dinámica**  
   - *Condición*: Si cola_B > 3 y existe cola_A → forzar paso de 1 trabajo A  
   - *Complejidad*: Balancear justicia vs. prevención de sobrecalentamiento

4. **Acceso exclusivo a bandeja**  
   - *Requerimiento*: Operación atómica para colocar trabajos  
   - *Riesgo*: Condición de carrera en actualización de colas

## 2. Identificación de Secciones Críticas

### Zonas de conflicto potencial:

| Sección Crítica | Riesgo | Consecuencia |
|-----------------|--------|--------------|
| Estado fotocopiadora | Race condition | Uso simultáneo |
| Contadores (A/B) | Inconsistencia | Conteos erróneos |
| Secuencia trabajos B | Conteo incorrecto | Enfriamientos mal calculados |
| Bandeja de entrada | Trabajos perdidos | Inanición |

### Estrategia de protección:
- **Aislamiento atómico** para cada sección crítica
- **Minimización** del tiempo en zonas críticas
- **Jerarquía** de bloqueos para evitar deadlocks

## 3. Diseño de Semáforos

### Semáforos principales y su propósito:

1. **`mutex_fotocopiadora`** (Binario)
   - *Función*: Garantizar acceso exclusivo al dispositivo físico
   - *Analogía*: "Llave" de la fotocopiadora
   - *Implementación*: 
     ```c
     sem_init(&mutex_fotocopiadora, 0, 1); // Inicialmente libre
     ```

2. **`mutex_bandeja`** (Binario)
   - *Función*: Serializar acceso a la bandeja de entrada
   - *Importancia*: Previene corrupción de colas

3. **Semáforos de cola** (Contadores)
   - `sem_trabajoA`: Trabajos tipo A pendientes
   - `sem_trabajoB`: Trabajos tipo B pendientes
   - *Mecanismo*: 
     ```c
     sem_post(&sem_trabajoA); // Añade a cola A
     sem_wait(&sem_trabajoB); // Espera en cola B
     ```

4. **`sem_enfriamiento`** (Binario)
   - *Comportamiento*:
     - 1 = Operación normal
     - 0 = En enfriamiento
   - *Transición*:
     ```c
     sem_wait(&sem_enfriamiento); // Inicia cooldown
     sleep(5);                   // Espera 5s
     sem_post(&sem_enfriamiento);// Reactiva
     ```

5. **`mutex_contadores`** (Binario)
   - *Protege*:
     - `contador_trabajosB_seguidos`
     - `trabajosA_espera`
     - `trabajosB_espera`
   - *Patrón*:
     ```c
     sem_wait(&mutex_contadores);
     // Actualizar valores
     sem_post(&mutex_contadores);
     ```