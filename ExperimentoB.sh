#!/bin/bash

# Lista de archivos de entrada
archivos=("datos1.txt" "datos2.txt" "datos3.txt" "datos4.txt" "datos5.txt" "datos6.txt" "datos7.txt" "datos8.txt" "datos9.txt" "datos10.txt" "datos11.txt" "datos12.txt" "datos13.txt" "datos14.txt" "datos15.txt" )

resultado="ResultadosB.txt"

# Agrega un encabezado al archivo de resultados
echo "Tamaño, Tiempo, Memoria" > "$resultado"

for archivo in "${archivos[@]}"
do
  # Muestra cuál archivo está procesando
  echo "Ejecutando ./t1.exe con $archivo"

  # Extrae la primera línea del archivo (tamaño de datos)
  tamano=$(head -n 1 "$archivo")

  # Ejecuta el programa en C y captura la salida
  salida=$(./t1.exe 1 -2 -S < "$archivo")

  # Agrega el tamaño y la salida del programa a una línea en el archivo de resultados
  echo "$tamano, $salida" >> "$resultado"
done

echo "Todos los archivos han sido procesados. Resultados almacenados en $resultado."
