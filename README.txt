Modo de compilacion : gcc t1.c -o t1.exe
Modo de ejecucion: ./t1.exe -N -P -O < data.txt
Donde 			-N: Tamano memoria
			-P Modo de ejecucion {1: Clasico, 2: 2 digitos por byte, 3: Cambio de base}
			-O {V: verboso, S: silencioso}
Para replicar experimento correr 3 scripts sh de la siguiente manera
./ExperimetnoA.sh //Modo clasico 
./ExperimentoB.sh // Modo 2 digitos por byte
./ExperimentoC.sh // Modo cambio de base 256

Los 3 script usan todos los datos de prueba incluidos en el archivo, desde el datos.txt al datos15.txt 