/*
    Nombre: Ejercicio7.c
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    Ejercicio 7: Escribe un programa que acepte como argumentos el nombre de un programa, sus argumentos si los tiene, y opcionalmente la cadena “bg”.
    Nuestro programa deberá ejecutar el programa pasado como primer argumento en foreground si no se especifica la cadena "bg" y en background en caso 
    contrario. Si el programa tiene argumentos hay que ejecutarlos con estos 

    Ejecucion del programa: $> ./ejercicio6
*/


#include <stdlib.h> // exit
#include <stdio.h> // perror
#include <unistd.h> // fork
#include <sys/types.h> // pid_t
#include <sys/wait.h> // waitpid
#include <string.h> // strcmp


int main (int argc, char *argv[]){

    // 1. compruebo los argumentos , al menos un argumento (nombre del programa a ejecutar)
    if (argc < 2){
        perror("Error en el numero de argumentos: ./ejercicio7 <nombre_programa> <argumentos_programa> <bg>\n");
        exit(EXIT_FAILURE);
    }

    // 2. comrpuebo si ha pedido el argumento en background o no
    int background = 0;
    // el strcmp compara que el ultimo argumento pasado es bg o no
    if (argc > 2 && strcmp(argv[argc-1], "bg") == 0){
                background = 1;

        // eliminar el utlimo argumento "bg" por un &, que significa que es background
        argv[argc-1] = NULL; 
    }

    // 3. creo proceso hijo

    pid_t pid;


    if ((pid = fork()) < 0){
        perror("Error en el fork\n");
        exit(EXIT_FAILURE);
    } else if (pid == 0){
        // 4. caso hijo, ejecuto el programa con sus argumentos en el hijo
        // uso argv porque paso un array de argumentos &argv[1] 
        execvp(argv[1], &argv[1]);
        
        // el caso error en un exec no hace falta if
        perror("Error en el execvp\n");
        exit(EXIT_FAILURE);

    } 

    // 5. caso padre , else 
    // es background o no 

    if (background){
        // 6. ejecucion background 
        printf("Ejecucion en background\n. PID: %d\n", pid);    
    } else {
        // 7. ejecucion foreground
        // espero a que el hijo termine 
        int estado;
        //wait(&estado);
        waitpid(pid, &estado, 0);
        printf("\nMi hijo %d ha finalizado con el estado %d\n", pid, estado >> 8);
    }
    




    return EXIT_SUCCESS;
}