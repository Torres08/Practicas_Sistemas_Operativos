/*

    Nombre: Ejercicio2. Contador
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    Ejercicio 2:
*/

/*

    Ejecucion del programa: 
    
    $> ./ejercicio2 &
    No se puede tratar la señal 0
    No se puede tratar la señal 9
    No se puede tratar la señal 19
    No se puede tratar la señal 32
    No se puede tratar la señal 33

    $>ps
        338638 pts/0    00:00:31 ejercicio2

    $> kill -s SIGUSR1 338638

    $> kill -SIGINT 338638  
        Señal 2 recibida. Total de veces: 1

    $> kill -111 338638
        bash: kill: 111: invalid signal specification
    
    $> kill -KILL 338638
        terminamos el proceso
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

// Variables globales
// Arreglo para contar la cantidad de veces que se recibe cada señal
int contador[NSIG];

// 4. Función manejadora de señales
void handler_contador(int signo)
{
    // Verificar si la señal puede manejarse
        // Incrementar el contador de la señal correspondiente
        contador[signo]++;
        // Mostrar la señal y la cantidad de veces que se ha recibido
        printf("Señal %d recibida. Total de veces: %d\n", signo, contador[signo]);
    
    
}

int main()
{

    // 1. struct asignaction
    struct sigaction sa;

    // 2. setvbuf
    setvbuf(stdout, NULL, _IONBF, 0);

    // 3. signo handler
    sa.sa_handler = handler_contador;

    // mascara
    sigemptyset(&sa.sa_mask);

    // 5. flags,
    sa.sa_flags = SA_RESTART;

    // 6. inicializar el contador
    for (int i = 0; i < NSIG; i++)
    {
        contador[i] = 0;
    }

    // 7. bucle 60 señales
    for (int i = 0; i < NSIG; i++)
    {
        // 8. sigaction, la condicion indica señales que no puedo tratar
        // aqui es donde trato las señales que no puedo tratar 
        if ( i != 0 && i != 9 && i != 19 && i != 32 && i!= 33)
        {
            if (sigaction(i, &sa, NULL) == -1)
            {
                perror("Error en sigaction");
                fprintf(stderr, "No se uede manejar la señal %d\n", i);
                exit(EXIT_FAILURE);
            }
        } else {
            printf("No se puede tratar la señal %d\n", i);
        }
    }

    // bucle infinito para que le programa se ejecute
    // mientras no le mandemos señales para terminar
    while (1)
    {
        /* code */
    }

    return 0;
}