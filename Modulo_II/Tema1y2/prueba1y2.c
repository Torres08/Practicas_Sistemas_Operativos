/*
    Nombre: prueba.c
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    Prueba: resumen ejercicios tema 1 y 2 lo más importante, a estudiar

    Contar numero archivos regulares en un directorio dado y mostrar resultado
        1. comprobar argumentos correctos
        2. abrir directorio
        3. detectar archivos regulares
        4. "Mi numero es <n_entero> " escribirlo en los archivos detectados

    Modificaciones
        5. abrir archivos -> O_TRUNC -> 0_APPEND (cambiarlo por append)
           mostrar contenido anterior del archivo y agregar la nueva linea

    Ejecucion del programa: $> ./prueba <path_dir> <n_entero>

*/

#include <stdio.h>        // funciones entrada y salida (printf)
#include <stdlib.h>       // incluye funciones como atoi (convierte una cadena a un entero)
#include <dirent.h>       // para el manejo de directorios
#include <errno.h>        // para el manejo de errores
#include <sys/stat.h>     // para el manejo de archivos
#include <fcntl.h>        // para el manejo de archivos
#include <unistd.h>       // para el manejo de archivos
#include <string.h>       // para el manejo de cadenas , strcmp, comparar strings
#include <linux/limits.h> // para PATH_MAX

#include <ftw.h> // para la funcion nftw()



int main(int argc, char *argv[])
{

    // 1. comprobar argumentos correctos
    if (argc != 3)
    {
        perror("Error en el numero de argumentos, Uso:$> ./prueba <path_dir> <n_entero>");
        return EXIT_FAILURE;
    }

    // 2. datos que necesito, path y n_entero y un contador
    // const char *path = argv[1]; // puede ser un char simplemente, como sea

    char path[500]; // dos formas de hacerlo
    strcpy(path, argv[1]);

    int n_entero = atoi(argv[2]); // atoi convierte una cadena a un entero
    int contador = 0;

    // cuando trabajo con directorios es necesario su DIR y struct dirent
    DIR *directorio;
    struct dirent *entrada;
    struct stat atributos; // mejor declaralo aqui que en while

    int fd; // para abrir el archivo

    // 3. abrir directorio, no quiero que sea nulo
    if ((directorio = opendir(path)) == NULL)
    {
        perror("Error al abrir el directorio");
        return EXIT_FAILURE;
    }

    // 4. vamos leyendo las entradas del bucle = leemos el directorio
    while ((entrada = readdir(directorio)) != NULL)
    {

        // 7. Ignorar los directorios "." y ".."
        if (strcmp(entrada->d_name, ".") == 0 || strcmp(entrada->d_name, "..") == 0)
            continue;
        ;

        // 9. voy a escribir tambien el path del archivo
        // en verdad no hace falta el path, puedo abrirlo directamente
        char path_archivo[PATH_MAX];
        snprintf(path_archivo, sizeof(path_archivo), "%s/%s", path, entrada->d_name);
        // printf("Path: %s\n", path_archivo);

        // 5. saco atributos de la entrada+
        if (stat(path_archivo, &atributos) < 0)
        {
            perror("Error al sacar atributos");
            return EXIT_FAILURE;
        }

        // 6. si es un archivo regular, pasa por el macro S_ISREG el atributo st_mode
        if (S_ISREG(atributos.st_mode))
        {
            contador++;

            // 8. creo un buffer para el mensaje y lo escribo en el archivo
            // snprintf permite escribir un mensaje en un buffer
            char mensaje[100];
            snprintf(mensaje, sizeof(mensaje), "Mi numero es %d \n", n_entero);

            // 10. abro el archivo
            if ((fd = open(path_archivo, O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0)
            {
                perror("Error al abrir el archivo");
                return EXIT_FAILURE;
            }

            // 11. escribo el mensaje en el archivo
            if (write(fd, mensaje, strlen(mensaje)) == -1)
            {
                perror("Error al escribir en el archivo");
                return EXIT_FAILURE;
            }

            // 12. cierro el archivo
            close(fd);
        }
    }

    // 11. cerramos fuera del while
    closedir(directorio);

    // recuerda que solo leemos el directorio no subdirectorios de este, recomendable usar nftw si nos pide subdirectorios
    printf("numero total de archivos regulares en %s : %d\n", path, contador);

    return EXIT_SUCCESS;
}


