/*

    Nombre: Ejercicio1
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    Ejercicio 1: Conpila y comprende el programa 
*/


/*
 envioSignal.c
 Trabajo con llamadas al sistema del Subsistema de Procesos conforme a POSIX 2.10
 Utilización de la llamada kill para enviar una señal:
 0: SIGTERM
 1: SIGUSR1
 2: SIGUSR2
  a un proceso cuyo identificador de proceso es PID.
 SINTAXIS: envioSignal [012] <PID>
*/

/*
    Ejecucion del programa: 
    $> ./reciboSignal & (en segundo plano)
    $> ps 
        PID TTY          TIME CMD
        102996 pts/2    00:00:00 bash
        188272 pts/2    00:00:15 reciboSignal
        189473 pts/2    00:00:00 ps

    copio el pid del proceso reciboSignal, en este caso 188272

    $> ./envioSignal 2 188272 // mensaje 2
    $> ./envioSignal 1 188272 // mensaje 1
    $> ./envioSignal 0 188272 // termina el proceso


*/

#include <sys/types.h> //POSIX Standard: 2.6 Primitive System Data Types
#include <limits.h>    //Incluye <bits/posix1_lim.h> POSIX Standard: 2.9.2 //Minimum    //Values Added to <limits.h> y <bits/posix2_lim.h>
#include <unistd.h>    //POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    // 1. creo un pid y una variable signal
    long int pid;
    int signal;

    // 2. compruebo que el numero de argumentos es correcto
    if (argc < 3)
    {
        printf("\nSintaxis de ejecucion: envioSignal [012] <PID>\n\n");
        exit(EXIT_FAILURE);
    }

    // 3. convierto el pid a long int
    pid = strtol(argv[2], NULL, 10);

    // 4. compruebo que el pid es correcto, funcion dada, no es importante 
    if (pid == LONG_MIN || pid == LONG_MAX)
    {
        if (pid == LONG_MIN)
            printf("\nError por desbordamiento inferior LONG_MIN %ld", pid);
        else
            printf("\nError por desbordamiento superior LONG_MAX %ld", pid);
        perror("\nError en strtol");
        exit(EXIT_FAILURE);
    }

    // 5. signal es el primer argumento, lo convierto a int
    signal = atoi(argv[1]);

    // 6. segun el signal envio señal a pid de SIGTERM, SIGUSR1 o SIGUSR2
    switch (signal)
    {
    case 0: // SIGTERM, señal de terminacion
        kill(pid, SIGTERM);
        break;
    case 1: // SIGUSR1, señal definica por el usuario 1
        kill(pid, SIGUSR1);
        break;
    case 2: // SIGUSR2, señal definica por el usuario 2
        kill(pid, SIGUSR2);
        break;
    default: // not in [012]
        printf("\n No puedo enviar ese tipo de señal");
    }
}