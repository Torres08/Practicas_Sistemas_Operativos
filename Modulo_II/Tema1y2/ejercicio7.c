/*

    Nombre: Ejercicio7.c
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    Ejercicio 7: Programa una nueva orden que recorra la jerarquía de subdirectorios existentes a partir de uno dado como argumento
    y devuelva la cuenta de todos aquellos archivos regulares que tengan permiso de ejecución para el grupo y para otros.
    Ademas del nombre de los archivos encontrados, deberá devolver sus números de inodo y la suma total de espacio ocupado por
    dicho archivo. EL formato de la nueva orden será
    Ejecucion del programa: $> ./ejercicio7 <pathname>

    pathname es la ruta del directorio a partir del cual queremos que empiece a analizar la estructura del árbol de subdirectorios. EN caso que no de argumentos
    tomara como punto de partida el directorio actual Ejemplo de salida despues de ejecutar el programa:

    Los i-nodos son:
    ./recursos/archivo1  55
    ./recursos/archivo2  56
    ./recursos/carpeta/texto.txt 57

    ....
    Existian 3 archivos regulares con permiso x para grupo y otros
    El tamaño total ocupado por dichos archivos es X bytes

    -rw-r--r-- 1 torres torres     0 Dec 17 13:03  hola.txt
    drwx------ 2 torres torres  4096 Sep 13  2017  Sesion1
    drwx------ 2 torres torres  4096 Sep 13  2017  Sesion2
    drwx------ 2 torres torres  4096 Sep 13  2017  Sesion3
    drwx------ 2 torres torres  4096 Sep 13  2017  Sesion4
    drwx------ 2 torres torres  4096 Sep 13  2017  Sesion5
    drwx------ 2 torres torres  4096 Sep 13  2017  Sesion6
    drwx------ 2 torres torres  4096 Sep 13  2017  Sesion7
    drwxr-xr-x 4 torres torres  4096 Sep 19 09:53  Sistemas_Operativos_old
    -rw-r--r-- 1 torres torres 18649 Dec 15 13:01 'SO-P-Todos_MaterialModulo2(1).zip'
*/

#include <linux/limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

// definicion de la funcion
// varios pathnames: subdirectorios y directorios
void buscar_recursivo(DIR *directorio, char pathname[], int *n, int *st_size);

int main(int argc, char *argv[])
{

    // 1. creo las variables que voy a necesitar
    DIR *directorio;
    char *pathname;
    char pathname_none[] = ".";
    int n = 0;       // n archivos regulares
    int st_size = 0; // tamaño total de los archivos

    // 2. compruebo que se pasa un argumento, caso 0 uso pathname_none que es basicamente indicar que es el directorio actual
    if (argc == 2)
        pathname = argv[1];
    else
        pathname = pathname_none;

    // 3. abro el directorio inicializando mi DIR
    if ((directorio = opendir(pathname)) == NULL)
    {
        perror("\nError en opendir");
        exit(EXIT_FAILURE);
    }

    // 4. uso la funcion recursiva para buscar los archivos y rellenar las variables n y st_size
    printf("pathname seleccionado: %s\n", pathname);
    printf("Los i-nodos son:\n");
    buscar_recursivo(directorio, pathname, &n, &st_size);

    printf("Existen %u archivos regulares con permiso x para grupo y otros\n", n);
    printf("El tamaño total ocupado por dichos archivos es %lu bytes\n", st_size);

    return EXIT_SUCCESS;
}

void buscar_recursivo(DIR *directorio, char pathname[], int *n, int *st_size)
{

    // 5. variables que necesito, estructura directorio, atributos , bufer y DIR otra vez
    DIR *subdirectorio;
    struct dirent *entrada;
    struct stat atributos;
    char cadena[PATH_MAX];

    // 6. leo el directorio, mientras pueda leer, mietras haya suybdirectorio
    while ((entrada = readdir(directorio)) != NULL)
    {
        // 7. no quiero ni . ni .. asi que los salto
        // strcmp compara cadenas caracteres
        if (strcmp(entrada->d_name, ".") != 0 && strcmp(entrada->d_name, "..") != 0)
        {

            // 8. creo la cadena con el pathname y el nombre del archivo /prueba/archivo1.txt
            sprintf(cadena, "%s/%s", pathname, entrada->d_name);

            // 9. obtengo los atributos del archivo con la llamada al sistema lstat
            if (stat(cadena, &atributos) < 0)
            {
                perror("\nError en lstat");
                exit(EXIT_FAILURE);
            }

            // 11. caso en el que es un directorio, llamo a la funcion recursiva
            if (S_ISDIR(atributos.st_mode))
            {
                // 12. abro el directorio
                if ((subdirectorio = opendir(cadena)) == NULL)
                {
                    perror("\nError en opendir");
                    exit(EXIT_FAILURE);
                }
                // 13. llamo a la funcion recursiva
                buscar_recursivo(subdirectorio, cadena, n, st_size);
                closedir(subdirectorio);
            }
            else
            {

                // 10. condicion: sea archivp regular y tenga permisos de ejecucion para grupo y otros
                if (S_ISREG(atributos.st_mode) &&
                    (atributos.st_mode & (S_IXGRP | S_IXOTH)))
                {
                    // 11. imprimo el nombre del archivo, el inodo y el tamaño
                    printf("%s %lu %lu\n", cadena, atributos.st_ino, atributos.st_size);
                    // 12. incremento el numero de archivos y el tamaño total
                    (*n)++;                        // +1 archivo regular
                    *st_size += atributos.st_size; // añado el tamaño de dicho archivo
                }
            }
        }
    }
}