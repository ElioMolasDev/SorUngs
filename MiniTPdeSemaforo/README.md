# Fotocopiadora Rebelde - Solución con Semáforos

![Dinosaurios en la universidad](https://via.placeholder.com/800x400?text=Universidad+de+los+Dinosaurios)

## 📝 Enunciado del Problema

En la Universidad de los Dinosaurios existe una fotocopiadora rebelde con comportamiento especial:

- **Restricciones**:
  - Solo un dinosaurio puede usarla a la vez
  - 2 trabajos tipo B seguidos → 5s de enfriamiento obligatorio
  - Si hay >3 trabajos B esperando → forzar paso de 1 trabajo A
  - Acceso exclusivo a la bandeja de trabajos

- **Tipos de trabajo**:
  - **Tipo A**: Textos teóricos (rápidos)
  - **Tipo B**: Prácticas con imágenes (lentos, recalientan)

## 🛠️ Solución Implementada

### 🔒 Semáforos Utilizados

| Semáforo | Tipo | Función |
|----------|------|---------|
| `mutex_fotocopiadora` | Binario | Controla acceso físico a la máquina |
| `mutex_bandeja` | Binario | Protege la bandeja de trabajos |
| `sem_trabajoA` | Contador | Trabajos tipo A en espera |
| `sem_trabajoB` | Contador | Trabajos tipo B en espera |
| `sem_enfriamiento` | Binario | Controla estado de enfriamiento |
| `mutex_contadores` | Binario | Protege variables compartidas |

### 📊 Variables Compartidas

```c
int contador_trabajosB_seguidos = 0;  // Conteo de B consecutivos
int trabajosA_espera = 0;             // Cola de trabajos A
int trabajosB_espera = 0;             // Cola de trabajos B
int fotocopiadora_ocupada = 0;        // Estado actual