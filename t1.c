/***************************************************************************************
 * 
 * t1.c: Experimento multiplicacion de numeros naturales con 3 acercamientos distintos
 *
 * Programmer: Vicente Santos Varas
 *
 * Santiago de Chile, 21/10/2024
 *
 **************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

long long unsigned int Memory = 0;
long long unsigned int Memory_limit;

void AddMemory(size_t size) {
    Memory = Memory + size;
}

void SubMemory(size_t size) {
    Memory = Memory - size;
}


void Usage(unsigned char *mess) {

    printf("\nUsage: %s -N -P -O < data.txt\n",mess);
    printf("N = numero de bytes de memoria\n");
    printf("P = {N: 1 Digito por byte, M: 2 Digitos por byte, B: Cambio de 10}\n");
    printf("O = {S: modo silencioso, V: modo vervoso}\n\n");
}


/*
 *
 */ //Llenar arreglos
void FillArray(unsigned char *array, int size) {
    int i;
    for (i = 0; i < size ; i = i + 1) {
        scanf("%hhu", &array[i]);
    }    
}


/*
 *
 */ //Llenar arreglos con 2 digitos por byte
void FillArrayBits(unsigned char *array, int size) {
    unsigned int count = 0, i;
    unsigned char d1, d2;

    for (i = 0; i < (size + 1) / 2; i = i + 1) {
        scanf("%hhu", &d1);
        count = count + 1;
        if (count != size){
            scanf("%hhu", &d2);
            count = count + 1;
        }
        else{
            d2 = 0;
        }
        array[i] = (d1 << 4) | d2;  // Empaquetar los dos dígitos en un byte
    }
}


/*
 *
 */ //Obtener digito
unsigned char GetDigit(unsigned char *array, int pos) {
    unsigned int bpos = pos / 2;

    if (pos % 2 == 0) {
        return (array[bpos] >> 4) & 0xF;
    }
    else {
        return array[bpos] & 0xF;
    }
    
}


/*
 *
 */ //Almacenar digito
void SetDigit(unsigned char *array, int pos, unsigned char digit) {
    unsigned int bpos = pos / 2;
    if (pos % 2 == 0) {  
        array[bpos] = (array[bpos] & 0x0F) | (digit << 4);
    } else {  
        array[bpos] = (array[bpos] & 0xF0) | (digit & 0xF);
    }
}

/*
 *
 */ //Convertir decimal  a 256
 int Convert256(unsigned char *decimal, int size, unsigned char **b256) {
    unsigned char *temp = (unsigned char *)calloc(size, sizeof(unsigned char));
    unsigned int carry, current, i, b256Size = 0, tempempty = 1;

    for (i = 0; i < size; i = i + 1) {  
        temp[i] = decimal[i];
    }

    unsigned char *result = (unsigned char *)calloc(size / 2, sizeof(unsigned char));

    while (tempempty) {  //Mientras temp tenga digitos
        carry = 0;
        tempempty = 0;

        for (i = 0; i < size; i = i + 1) {        //Division por 256
            current = carry * 10 + temp[i];
            temp[i] = current / 256;  
            carry = current % 256;     
            if (temp[i] != 0) {
                tempempty = 1; 
            }
        }

        result[b256Size] = carry;                //Se guarda el resultado en result
        b256Size = b256Size + 1;
    }

    free(temp);
    *b256 = (unsigned char *)calloc(b256Size, sizeof(unsigned char));
    for (i = 0; i < b256Size; i = i + 1) {
        (*b256)[i] = result[i]; 
    }

    free(result);  
    return b256Size;   //se retorna el tamano
}

/*
 *
 */ //Convertir de 256 a decimal
int ConvertDecimal(unsigned char *base256, int size, unsigned char **decimal) {
    int i, j;
    unsigned int dSize = size * 3, current = 1, carry, value;   
    unsigned char *result = (unsigned char *)calloc(dSize, sizeof(unsigned char)); //Peor caso de tamaño, luego se reajusta

    for (i = size - 1; i >= 0; i = i - 1) {
        carry = base256[i]; // 

        for (j = 0; j < current; j = j + 1) {     //Transformacion a decimal
            value = result[j] * 256 + carry;
            result[j] = value % 10; 
            carry = value / 10;     
        }

        while (carry > 0) {
            result[current] = carry % 10;
            carry = carry / 10;
            current = current + 1;
        }
    }


    *decimal = (unsigned char *)calloc(current, sizeof(unsigned char));
    for (i = 0; i < current; i = i + 1) {
        (*decimal)[i] = result[i]; 
    }

    free(result); 

    
    return current;   //se retorna el tamano
}

/*
 *
 */ //Imprime resultado modo clasico
void PrintResultado(unsigned char *array, int size) {
    unsigned int i = 0;
     while (i < size && array[i] == 0) {
        i = i + 1;
    }
    printf("Resultado : ");
    for (i = i; i < size ; i = i + 1) {
        printf("%hhu", array[i]);

    }
    printf("\n");
}


/*
 *
 */ //Imprime resultado bits
void PrintResultadoBits(unsigned char *array, int size) {
    int i, start = size - 1; 
    unsigned char digit;

    
    while (start >= 0 && GetDigit(array, start) == 0) {
        start = start - 1;
    }

    printf("Resultado: ");
    for (i = start; i >= 0; i = i - 1) {
        digit = GetDigit(array, i);
        printf("%hhu", digit);
    }
    printf("\n");
}


/*
 *
 */ //Imprime resultado 256
void PrintResultado256(unsigned char *array, int size) {
    int i = size - 1;
    
    while (i >= 0 && array[i] == 0) {
        i = i - 1;
    }
    printf("Resultado 256 : ");
    for (i = i; i >= 0; i = i - 1) {
        printf("%hhu ", array[i]);
    }
    printf("\n");
}

/*
 *
 */
void PrintResultado2(unsigned char *array, int size) {   //Imprime resultado decimal del modo 256
    int i = size - 1;
    while (i >= 0 && array[i] == 0) {
        i = i - 1;
    }
    printf("Resultado decimal : ");
    for (i = i; i >= 0; i = i - 1) {
        printf("%hhu", array[i]);
    }
    printf("\n");
}

/*
 *
 */ //Imprime arreglos( a y b )
void PrintVariable(unsigned char *array, int size) {
    int i;
    for (i = 0; i < size ; i = i + 1) {
        printf("%hhu", array[i]);

    }
    printf("\n");
}


/*
 *
 */ //Imprime arreglos( a y b con 2 digitos por bit )
void PrintVariableBits(unsigned char *array, int size) {
    int i;
    unsigned char digit;
    for ( i = 0; i < size; i = i + 1) {
        digit = GetDigit(array, i);
        printf("%hhu", digit);
    }
    printf("\n");
}


/*
 *
 */ //Imprime arreglos a y b en base 256
void PrintVariable256(unsigned char *array, int size) {
    for (int i = size - 1; i >= 0; i = i - 1) {
        printf("%hhu ", array[i]);
    }
    printf("\n");
}


/*
 *
 */ //proceso de multiplicacion clasico
void Multiplicacion(unsigned char *a, int l, unsigned char *b, int m, unsigned char *resultado) {
    int i, j, k;
    unsigned char mult;
    AddMemory(sizeof(unsigned char));
    AddMemory(sizeof(int) * 3 );
    

    for (i = l - 1; i > -1; i = i - 1) {   
        for (j = m - 1; j > -1; j = j - 1) {  
            mult = a[i] * b[j];   
            k = i + j + 1;           
            resultado[k] = resultado[k] + mult;
            resultado[k - 1] = resultado[k - 1] + resultado[k] / 10;  
            resultado[k] = resultado[k] % 10;             
        }
    }
}


/*
 *
 */ //proceso de multiplicacion con 2 digitos por byte
void MultiplicacionBits(unsigned char *a, int l, unsigned char *b, int m, unsigned char *resultado) {
    // Inicializar el resultado a cero
    int temp, pos, nextpos, carry, i, j;
    unsigned char digita, digitb;
    AddMemory(sizeof(int) * 6);
    AddMemory(sizeof(char) * 2);
    for (i = 0; i < l; i = i + 1) {

        carry = 0; 

        for (j = 0; j < m; j = j + 1) {
            
            digita = GetDigit(a, l - 1 - i); // Obtener digitos
            digitb = GetDigit(b, m - 1 - j); 
            pos = i + j; // posicion resultado
            temp = digita * digitb + GetDigit(resultado, pos) + carry;            
            SetDigit(resultado, pos, temp % 10); 
            carry = temp / 10; // acarreo
        }
        nextpos = i + m; 
        while (carry > 0) {
            temp = carry + GetDigit(resultado, nextpos); // sumar el acarreo 
            SetDigit(resultado, nextpos, temp % 10); // guardar en el resultado
            carry = temp / 10; 
            nextpos = nextpos + 1; 
        }
    }
}


/*
 *
 */ //proceso de multiplicacion con base 256
void Multiplicacion256(unsigned char *a, int l, unsigned char *b, int m, unsigned char *resultado) {
    unsigned int carry, i, j, mult;
    for (i = 0; i < l; i = i + 1) {
        carry = 0;  
        for (j = 0; j < m; j = j + 1) {
            mult = a[i] * b[j] + resultado[i + j] + carry;
            resultado[i + j] = mult % 256;  
            carry = mult / 256;  
        }
        resultado[i + m] = resultado[i + m] + carry;  
    }
}


int main(int argc, unsigned char **argv) {
    float E_cpu;
    long E_wall;  
    time_t  ts, te;
    clock_t cs, ce;
    
    
        if (argc == 4) {
            unsigned int l, m;
            unsigned char *a, *b, *resultado;
            scanf("%u %u", &l, &m);
            Memory_limit = atoi(argv[1]);
            printf(" memoria limite %llu", Memory_limit);

            if(strcmp(argv[2], "-1") == 0) { //Modo multiplicacion digito a digito clasica 1 digito x byte
                a = (unsigned char *)calloc(l, sizeof(unsigned char));
                b = (unsigned char *)calloc(m, sizeof(unsigned char));
                resultado = (unsigned char*)calloc(l + m, sizeof(unsigned char));
                AddMemory(sizeof(unsigned char) * l);
                AddMemory(sizeof(unsigned char) * m);
                AddMemory(sizeof(unsigned char) * (l + m));




                FillArray(a, l);
                FillArray(b, m);

                if (strcmp(argv[3], "-V") == 0) {     //Verboos
                    printf("a : ");
                    PrintVariable(a, l);
                    printf("b : "); 
                    PrintVariable(b, m);

                }
                ts = time(NULL);
                cs = clock();
                Multiplicacion(a, l, b, m, resultado);   //Llamada a multiplicacion
                if (strcmp(argv[3], "-V") == 0)
                    PrintResultado(resultado, l+m);
                
                ce = clock();
                te = time(NULL);
                E_wall = (long) (te - ts);
                E_cpu = (float)(ce - cs) / CLOCKS_PER_SEC;
                        
                printf("Elapsed CPU Time: %f Wall Time: %ld Memory used: %llu Bytes\n", E_cpu, E_wall, Memory); 

            }
            else if(strcmp(argv[2], "-2") == 0) {        //Modo con 2 digitos por byte
                a = (unsigned char *)calloc((l + 1) / 2, sizeof(unsigned char));
                b = (unsigned char *)calloc((m + 1) / 2, sizeof(unsigned char));         
                resultado = (unsigned char *)calloc((l + m) / 2, sizeof(unsigned char));
                AddMemory(sizeof(unsigned char) * ((l + 1) / 2));
                AddMemory(sizeof(unsigned char) * ((m + 1) / 2));
                AddMemory(sizeof(unsigned char) * ((l + m) / 2));

                FillArrayBits(a, l);
                FillArrayBits(b, m);

                if (strcmp(argv[3], "-V") == 0) {  // Modo verboso
                    printf("a : ");
                    PrintVariableBits(a, l);
                    printf("b : ");
                    PrintVariableBits(b, m); 
                }

                // Realizar la multiplicación
                ts = time(NULL);
                cs = clock();
                MultiplicacionBits(a, l, b, m,  resultado);

                if (strcmp(argv[3], "-V") == 0)
                    PrintResultadoBits(resultado, l + m);
                ce = clock();
                te = time(NULL);
                E_wall = (long)(te - ts);
                E_cpu = (float)(ce - cs) / CLOCKS_PER_SEC;
                free(a);
                free(b);
                free(resultado);

                
                printf("Elapsed CPU Time: %f Wall Time: %ld Memory used: %llu Bytes\n", E_cpu, E_wall, Memory);


            }
            else if(strcmp(argv[2], "-3") == 0) {   //Modo cambio de base
                unsigned char *a = (unsigned char *)calloc(l, sizeof(unsigned char));
                unsigned char *b = (unsigned char *)calloc(m, sizeof(unsigned char));
                unsigned char *a256 = NULL;
                unsigned char *b256 = NULL;
                unsigned char *resultadoDecimal = NULL;
                int asize, bsize, dsize;


                FillArray(a, l);
                FillArray(b, m);
                ts = time(NULL);
                cs = clock();

                asize = Convert256(a, l, &a256);  // Conversion de las variables a base 256
                bsize = Convert256(b, m, &b256);
                unsigned char *resultado = (unsigned char *)calloc(asize + bsize, sizeof(unsigned char));
                AddMemory(sizeof(unsigned char) * asize);
                AddMemory(sizeof(unsigned char) * bsize);

                if (strcmp(argv[3], "-V") == 0) {
                    printf("a decimal : ");
                    PrintVariable(a, l);
                    printf("b decimal : ");
                    PrintVariable(b, m);
                    printf("a 256 : ");
                    PrintVariable256(a256, asize);
                    printf("b 256 : ");
                    PrintVariable256(b256, bsize);
                }

                // Realizar la multiplicación
                Multiplicacion256(a256, asize, b256, bsize, resultado);

                ce = clock();
                te = time(NULL);
                E_wall = (long)(te - ts);
                E_cpu = (float)(ce - cs) / CLOCKS_PER_SEC;

                if (strcmp(argv[3], "-V") == 0) {
                    PrintResultado256(resultado, asize + bsize);
                    dsize = ConvertDecimal(resultado, asize + bsize, &resultadoDecimal);
                    PrintResultado2(resultadoDecimal, dsize);
                }

                free(a);
                free(b);
                free(a256);
                free(b256);
                free(resultado);

                printf("Elapsed CPU Time: %f Wall Time: %ld Memory used: %llu Bytes\n", E_cpu, E_wall, Memory);
            }
            
        }
        else {
            Usage(argv[0]);
        }
}
   