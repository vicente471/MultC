#!/bin/bash

# Definir una lista de archivos a procesar
archivos_lista=(
    "datos1.txt" "datos2.txt" "datos3.txt" "datos4.txt" "datos5.txt"
    "datos6.txt" "datos7.txt" "datos8.txt" "datos9.txt" "datos10.txt"
    "datos11.txt" "datos12.txt" "datos13.txt" "datos14.txt" "datos15.txt"
)

archivo_salida="ResultadosA.txt"

# Añadir encabezado en el archivo de salida
echo "Tamaño, Tiempo, Memoria" > "$archivo_salida"

# Procesar cada archivo en la lista
for file in "${archivos_lista[@]}"; do
    # Mostrar archivo procesado
    echo "Procesando archivo: $file"

    # Leer el tamaño desde el primer dato del archivo
    primer_linea=$(head -1 "$file")

    # Ejecutar el programa con la entrada del archivo y almacenar la salida
    datos_procesados=$(./t1.exe 1 -1 -S < "$file")

    # Guardar los resultados en el archivo de salida
    echo "${primer_linea}, ${datos_procesados}" >> "$archivo_salida"
done

# Mensaje final al completar el procesamiento
echo "Procesamiento finalizado. Revisa los resultados en: $archivo_salida"
