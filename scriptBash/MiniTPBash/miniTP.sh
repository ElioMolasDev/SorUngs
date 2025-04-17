#!/bin/bash
if [ $# -eq 0 ]; then
    echo "Error: debe ejecutar con un parámetro"
    exit 1
fi
cd $HOME
mkdir "$1"
archivo="$HOME/$1/contenido_home.txt"
ls -la $HOME > "$archivo"
cat "$archivo"
read -p "Presione Enter para finalizar..."
