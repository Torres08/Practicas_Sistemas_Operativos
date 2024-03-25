/*

    Nombre: Ejercicio3.c Productor y Consumidor
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    Ejercicio 3: redirigiendo las entradas y salidas estandares de los procesos a los
    cauces podemos escribir un programa en lenguaje C que permita comunicar órdenes existentes sin
    necesidad de reprogramarlas, tal y como lo hace el shell. EN perticular,
    ejecute el siguiente programa que ilustra la comunicacion entre proceso padre e hijo a través
    de un cauce sin nombre redirigiendo la entrada estandar y la
    salida estandar del padre y el hijo respectivamente

    Ejecucion del programa: $>
*/

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[])
{

    // 1. para cauce sin nombre 2 descriptores 0 lecura 1 escritura, uno solo abierto a la vez
    int fd[2];
    pid_t PID;

    // 2. creo el cauce sin nombre
    pipe(fd); // Llamada al sistema para crear un pipe

    // 3. creo el proceso hijo
    if ((PID = fork()) < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (PID == 0)
    { 
        // 4. caso hijo 
        // ls
        // Establecer la direccion del flujo de datos en el cauce cerrando
        //  el descriptor de lectura de cauce en el proceso hijo
        close(fd[0]);

        // Redirigir la salida estandar para enviar datos al cauce
        //--------------------------------------------------------
        // Cerrar la salida estandar del proceso hijo
        close(STDOUT_FILENO);

        // Duplicar el descriptor de escritura en cauce en el descriptor
        // correspondiente a la salida estandar (stdout)
        dup(fd[1]);
        execlp("ls", "ls", NULL);
    }
    else
    { 
        // 4. caso padre 
        // sort. Estoy en el proceso padre porque PID != 0

        // Establecer la direcci�n del flujo de datos en el cauce cerrando
        //  el descriptor de escritura en el cauce del proceso padre.
        close(fd[1]);

        // Redirigir la entrada est�ndar para tomar los datos del cauce.
        // Cerrar la entrada est�ndar del proceso padre
        close(STDIN_FILENO);

        // Duplicar el descriptor de lectura de cauce en el descriptor
        // correspondiente a la entrada est�ndar (stdin)
        dup(fd[0]);
        execlp("sort", "sort", NULL);
    }

    return EXIT_SUCCESS;
}