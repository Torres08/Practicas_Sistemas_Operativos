/*

    Nombre: Ejercicio8.c
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    Ejercicio 8: Prueba el programa que recorre un sub-arbol con la funcion nftw().
    Ademas imlpementa de nuevo el ejercicio7 pero usando nftw().

    Ejecucion del programa: $> ./ejercicio8 pathname (si no se pasa pathname se usa el nombre del directorio actual)

*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h> // para PATH_MAX

#include <ftw.h> // para la funcion nftw()

// variables locales para n y st_size
int n = 0;
int st_size = 0;

int visitar(const char *path, const struct stat *atributos, int flags, struct FTW *ftwbuf)
{

    printf("Path:%s Modo: %o\n", path, atributos->st_mode);

    // devuelve siempre return 0
    return 0;
}

int buscar_recursivo(const char *path, const struct stat *atributos, int flags, struct FTW *ftwbuf)
{

    // ahora no hace falta ir leyendo manual solo combruebo
    // tmp saco atributos ya los tengo

    // ignorar directorios . y ..
    // Ignorar los directorios "." y ".."
    if (strcmp(path, ".") == 0 || strcmp(path, "..") == 0)
        return 0;

    // 4. caso base, si es un archivo regular y tiene permisos de ejecucion para grupo y otros
    if (S_ISREG(atributos->st_mode) &&
        (atributos->st_mode & (S_IXGRP | S_IXOTH)))
    {
        // 5. incremento y printf
        printf("%s %lu %lu\n", path, atributos->st_ino, atributos->st_size);
        n++;
        st_size += atributos->st_size;
    }

    // no hace falta caso recursivo por que el mismo nftw te lo hace
    return 0;
}
int main(int argc, char *argv[])
{

    // 1. comprobacion uso de nftw
    /*
    if (nftw(argc >= 2 ? argv[1] : ".", visitar, 10, 0) != 0) {
        perror("\nError en nftw");
        exit(EXIT_FAILURE);
    }
    */

    // 2. para el buscar regresivo, necesito un buffer
    char buffer[500]; // pathname

    if (argc == 2)
    {
        strcpy(buffer, argv[1]);
    }
    else
    {
        strcpy(buffer, ".");
    }

    // 3. uso la misma logica que en el ejercicio7.c, pero uso la funcion nftw
    printf("pathname seleccionado: %s\n", argv[1]);
    printf("Los i-nodos son:\n");
    
    if (nftw(buffer, buscar_recursivo, 10, 0)== -1){
        perror("\nError en nftw");
        exit(EXIT_FAILURE);
    }

    printf("Existen %u archivos regulares con permiso x para grupo y otros\n", n);
    printf("El tamaño total ocupado por dichos archivos es %lu bytes\n", st_size);

    return EXIT_SUCCESS;
}