/*

	Nombre: Ejercicio6.c
	Autores: Torres Ramos, Juan Luis
	Sistemas Operativos

	Ejercicio 6: 
    - acepte como entreada un argumento que representa el pathname de un directorio
    - otro argumento que es un nñumeor octal de 4 digitos (similar al que se puede utilizar para cambiar los permisos de un archivo con chmod)
    usa funcion strtol

    el programa tiene que usar el número octal indicado en el segundo argumento para cambiar los permisos de todos los archivos que se encuentren en el directorio
    indicado en el primer argumento

    el programa debe proporcionar en la slida estanndar una línea para cada archivo del directorio que este formada por
        <nombre_archivo> <permisos_antiguos> <permisos_nuevos>
    si no se puede cambiar los permisos de un determinado archivo se debe espeificar la siguiente info en la linea de salida
        <nombre_archivo> <errno> <permisos_antiguos>

	Ejecucion del programa: $> ./ejercicio6 <pahtname> <octal4dig>

*/



#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int main( int argc, char *argv[]){

    // 1. variables que necesito
    // directorio con su strict, stributos, un buffer, pathname y permisos
    DIR *directorio;
    struct dirent *entrada;
    struct stat atributos;
    char cadena[100];

    char *pathname;
    unsigned int permisos;
    unsigned int permisos_antiguos;

    // 2. compruebo que se pasan 2 argumentos
    if (argc != 3){
        perror("Error en el numero de argumentos");
        exit(EXIT_FAILURE);
    }

    // 3. inicializo las variables
    pathname = argv[1];
    // 4. strtol convierte el string de argv[2] a un long int
    permisos = strtol(argv[2], NULL, 8); // 8 es la base octal

    // 5. abro el directorio
    if ((directorio = opendir(pathname)) == NULL){
        perror("Error en opendir");
        exit(EXIT_FAILURE);
    }


    // 6. leo el directorio
    readdir(directorio);

    while ((entrada = readdir(directorio)) != NULL){

        // 7. creo la ruta completa del archivo
        sprintf(cadena, "%s/%s", pathname, entrada->d_name);

        // 8. obtengo los atributos del archivo
        if (lstat(cadena, &atributos) < 0){
            perror("Error en lstat");
            exit(EXIT_FAILURE);
        }

        // 9. compruebo que el archivo es regular
        if (S_ISREG(atributos.st_mode)){
            // 10. cambio los permisos del archivo
            if (chmod(cadena, permisos) < 0){
                perror("Error en chmod");
                exit(EXIT_FAILURE);
            }

            // 11. muestro por pantalla el nombre del archivo, los permisos antiguos y los nuevos
            printf("%s %o %o\n", entrada->d_name, atributos.st_mode, permisos);
        }
        else{
            // 12. muestro por pantalla el nombre del archivo, el errno y los permisos antiguos
            printf("%s %d %o\n", entrada->d_name, errno, atributos.st_mode);
        }
    }

    // 13. cierro el directorio
    closedir(directorio);

    // 14. veo con un ls -l los permisos del directorio nuevo
    execl("/bin/ls", "ls", "-l", pathname, NULL);

    exit(EXIT_SUCCESS);


}