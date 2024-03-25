
/*

    Nombre: Ejercicio2. Contador
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    Ejercicio 2: Reescribe el programa que implemente un encauzamiento de dos ordenes pero
    utilizando fcntl.Este programa admite 3 argumentos, el primero y el tercero serán dos ordenes de Linux
    El segundo argumento será el operador | (pipe) y el programa ejecutará las dos ordenes encauzadas

    Ejecucion del programa: ./ejercicio2 ls "|" sort

*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char **argv)
{
    // 1. compruebo los argumentos
    if (argc != 4)
    {
        perror("Error en el numero de argumentos. \n");
        exit(EXIT_FAILURE);
    }

    // 2. descriptor fd[2], PID, jugamos con cauces , como tarea 7.c, ejercicio tema 5
    int fd[2];
    pid_t PID;

    // 3. compruebo que han escrito el pipe
    if (strcmp(argv[2], "|") == 0)
    {
        // 4. creo el pipe
        if ((pipe(fd)) == -1){
            perror("Error en la creacion del pipe. \n");
        }

        // 5. creo el proceso hijo
        if ((PID = fork()) == -1){
            perror("Error en la creacion del proceso hijo. \n");
        }

        if (PID == 0){
            // 6. proceso hijo
            // el hijo se encarga de ejecutar el segundo argumento
            close(0); // cerramos la entrada estandar STDIN_FILENO
            close(fd[1]); // cerramos el descriptor de escritura

            // duplicamos el descriptor de lectura del pipe en la entrada estandar
            fcntl(fd[0], F_DUPFD, 0);

            // ejecutamos el segundo argumento
            execlp(argv[3], argv[3], NULL);

        }else {
            // 7. proceso padre
            // el padre se encarga de ejecutar el primer argumento

            close(1); // cerramos la salida estandar STDOUT_FILENO
            close(fd[0]); // cerramos el descriptor de lectura

            fcntl(fd[1], F_DUPFD, 1); // duplicamos el descriptor de escritura del pipe en la salida estandar 

            // ejecutamos el primer argumento 
            execlp(argv[1], argv[1], NULL);   
        }
    }
    else
    {
        perror("modo uso: ./ejercicio2 <argumento1> \"|\" <argumento2> \n");
    }
}