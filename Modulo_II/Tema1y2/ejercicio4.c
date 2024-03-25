/*

    Nombre: Ejercicio4.c
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    Ejercicio 4: Define una macro en lenguaje C que tenga la misma funcionalidad que la macro S_ISREG(mode)
    usando para ello los flags definidos en <sys/stat.h> para el campo st_mode de la struct stat
    y comprueba que funciona en un programa simple. COnsulta en un libro de C o en internet como se especifica una macro con argumentos 
    en C


    Ejecucion del programa: ./ejercicio4 archivo.txt
                            
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // para stat
#include <sys/types.h>
#include <unistd.h>


// 1. definicion de macro
// S_ISREG(mode) 	es un archivo regular?
// macro se basa en comparar el bit S_IFREG, si es regular dicho bit es 1, si no es 0

#define mimacro_S_ISREG(mode) (((mode_t)(mode)&S_IFREG) ? 1 : 0)

int main (int argc, char *argv[]){

    // 2. creo variable stat y un buffer char de 30 bytes
    struct stat atributos;
    char tipoArchivo[30];

    char tipoArchivo2[30];

    // 3. compruebo que se pasa un argumento

    if (argc != 2){
        printf("\nError, invalid number of arguments\nUso: ejercicio4 <archivo>\n");
        exit(EXIT_FAILURE);
    }

    // 4. leo los datos de mi archivo, solo introduzco un archivo
    if (lstat(argv[1], &atributos) < 0){

        printf("\nError al intentar acceder a los atributos de %s", argv[1]);
        perror("\nError en lstat");

    } else {

        // 5. Compruebo si mi macro esta bien, el error que da olvidalo, corre sin problemas
        if (mimacro_S_ISREG(atributos.st_mode)){
            strcpy(tipoArchivo, "Regular");
        } else {
            strcpy(tipoArchivo,"Tipo de archivo desconocido");
        }

        if (S_ISREG(atributos.st_mode)) 
            strcpy(tipoArchivo2,"Regular");
        else 
            strcpy(tipoArchivo2,"Tipo de archivo desconocido");
 
        // 6. imprimo el resultado
        printf("Con mimacro: %s \n",tipoArchivo);
        printf("Con S_ISREG: %s \n",tipoArchivo2);
    }


}