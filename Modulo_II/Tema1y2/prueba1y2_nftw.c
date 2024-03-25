/*

	Nombre: prueba_nftw.c
	Autores: Torres Ramos, Juan Luis
	Sistemas Operativos

	prueba_nftw.c: version de prueba pero usando nftw y recorriendo subdirectorios

	Ejecucion del programa: $> ./ejercicio3 <nombre_archivo1>    <nombre_archivo2> ... <nombre_archivoN>

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

// variable local
int contador = 0;

// version con subdirectorios, uso nftw, asi no uso tantas llamadas al sistema de open y eso
int buscar_recursivo(const char *path, const struct stat *atributos, int flags, struct FTW *ftwbuf)
{
    // no queremos ni . ni ..
    if (strcmp(path, ".") == 0 || strcmp(path, "..") == 0)
        return 0;

    // caso archivo es regular
    if (S_ISREG(atributos->st_mode))
    {
        contador++;

        // creo el mensaje
        char mensaje[100];
        snprintf(mensaje, sizeof(mensaje), "Mi numero es %s\n", getenv("N_ENTERO"));

        int fd;

        // abro el archivo
        if ((fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0666)) < 0)
        {
            perror("Error al abrir el archivo");
            return EXIT_FAILURE;
        }

        //  escribo el mensaje en el archivo
        if (write(fd, mensaje, strlen(mensaje)) == -1)
        {
            perror("Error al escribir en el archivo");
            return EXIT_FAILURE;
        }
        // cierro descriptor
        close(fd);
    }

    // simepre return 0
    return 0;
}


int main(int argc, char *argv[]){

    // compruebo numero de argumentos
    if (argc != 3)
    {
        perror("Error en el numero de argumentos, Uso:$> ./prueba <path_dir> <n_entero>");
        return EXIT_FAILURE;
    }


    // para este caso, yo no puedo pasar nuevas variables a nftw, asi que
    // lo que hago es pasar todas las variables a entrono/globales
    const char *path = argv[1];
    setenv("N_ENTERO", argv[2], 1); // Establecer la variable de entorno

    if (nftw(path, buscar_recursivo, 10, 0) == -1 ){
        perror("Error en nftw");
        return EXIT_FAILURE;
    }

    printf("Numero de archivos regulares: %d\n", contador);

    return EXIT_SUCCESS;


}