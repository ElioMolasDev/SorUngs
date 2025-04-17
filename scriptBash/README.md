# Comandos Linux y script
<details>
<summary> # 📁 Comandos esenciales de Linux (click para expandir)</summary>

## 🔍 Navegación y exploración

| Comando | Descripción | Ejemplo |
|--------|-------------|---------|
| `pwd` | Muestra la ruta actual. | `pwd` → `/home/usuario` |
| `ls` | Lista archivos y carpetas. | `ls` |
| `ls -la` | Lista todo (incluye ocultos) con detalles. | `ls -la` |
| `cd nombre/` | Entra al directorio `nombre/`. | `cd Documentos/` |
| `cd ..` | Sube un nivel. | `cd ..` |
| `cd` o `cd ~` | Va al home del usuario. | `cd` |
| `tree` | Muestra la estructura de carpetas (requiere instalación). | `tree ~/Documentos` |

## 🛠️ Gestión de archivos y carpetas

| Comando | Descripción | Ejemplo |
|--------|-------------|---------|
| `mkdir nombre` | Crea una carpeta. | `mkdir proyectos` |
| `touch archivo.txt` | Crea un archivo vacío. | `touch notas.txt` |
| `cp archivo1 archivo2` | Copia archivos. | `cp notas.txt copia.txt` |
| `mv origen destino` | Mueve o renombra archivos/carpetas. | `mv notas.txt Documentos/` |
| `rm archivo.txt` | Borra archivo. | `rm copia.txt` |
| `rm -r carpeta/` | Borra carpeta y su contenido. | `rm -r backups/` |
| `nano archivo.txt` | Abre el archivo en el editor de texto terminal. | `nano notas.txt` |

## 📦 Comprimir y descomprimir

| Comando | Descripción | Ejemplo |
|--------|-------------|---------|
| `tar -czf archivo.tar.gz carpeta/` | Comprime a `.tar.gz`. | `tar -czf backup.tar.gz Documentos/` |
| `tar -xzf archivo.tar.gz` | Descomprime `.tar.gz`. | `tar -xzf backup.tar.gz` |
| `zip -r archivo.zip carpeta/` | Comprime a `.zip`. | `zip -r proyecto.zip proyecto/` |
| `unzip archivo.zip` | Descomprime `.zip`. | `unzip proyecto.zip` |

## 🔍 Búsqueda

| Comando | Descripción | Ejemplo |
|--------|-------------|---------|
| `find . -name "*.txt"` | Busca archivos por nombre. | `find . -name "log*.txt"` |
| `grep "palabra" archivo.txt` | Busca texto dentro de un archivo. | `grep "error" log.txt` |
| `grep -r "palabra" carpeta/` | Busca dentro de múltiples archivos. | `grep -r "clave" src/` |

## 📋 Información del sistema

| Comando | Descripción | Ejemplo |
|--------|-------------|---------|
| `df -h` | Uso del disco (legible). | `df -h` |
| `free -h` | Uso de memoria RAM. | `free -h` |
| `top` | Procesos activos. | `top` |
| `htop` | Interfaz avanzada de procesos. | `htop` |
| `uname -a` | Info del sistema operativo. | `uname -a` |
| `uptime` | Tiempo de actividad del sistema. | `uptime` |

## 🔑 Permisos y usuarios

| Comando | Descripción | Ejemplo |
|--------|-------------|---------|
| `chmod +x archivo.sh` | Da permisos de ejecución. | `chmod +x script.sh` |
| `chown usuario:grupo archivo` | Cambia el propietario. | `chown usuario:usuarios archivo.txt` |
| `whoami` | Muestra el usuario actual. | `whoami` |
| `sudo comando` | Ejecuta como administrador. | `sudo apt update` |

## 🧪 Programación en Bash

| Comando | Descripción | Ejemplo |
|--------|-------------|---------|
| `#!/bin/bash` | Línea inicial de todo script Bash. | `#!/bin/bash` |
| `echo "Hola"` | Imprime texto. | `echo "Hola Mundo"` |
| `read var` | Guarda input del usuario. | `read nombre` |
| `if`, `else`, `fi` | Condicionales. | `if [ $x -eq 5 ]; then echo "ok"; fi` |
| `for`, `while`, `do`, `done` | Bucles. | `for i in *; do echo $i; done` |

## ⚙️ Otros útiles

| Comando | Descripción | Ejemplo |
|--------|-------------|---------|
| `history` | Muestra historial de comandos. | `history` |
| `clear` | Limpia la terminal. | `clear` |
| `man comando` | Manual del comando. | `man ls` |
| `exit` | Cierra terminal o script. | `exit` |
EOF
</details>
