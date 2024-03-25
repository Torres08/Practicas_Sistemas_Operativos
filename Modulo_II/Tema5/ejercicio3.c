/*

    Nombre: tarea9.c Ejemplo de manejador señal SIGINT
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    Tarea 9: ejemplo llamada al sistema sigaction para estrablecer un manejador para la señal SIGINT

    Ejecucion del programa: $> ./Tarea9

    Escribe un programa que suspenda la ejecución del proceso actual hasta que se reciba la señal SIGUSR1. Consulta en el manual en línea sigemptyset para conocer las distintas operaciones que permiten configurar el conjunto de señales de un proceso.

    ./sigsuspend_example
    ps aux | grep sigsuspend_example
    ps aux | grep sigsuspend_example
        Programa suspendido. Esperando la señal SIGUSR1...
        Señal SIGUSR1 recibida. Programa reanudado
*/

/*

    - si envio sigusr2 
    Programa suspendido. Esperando la señal SIGUSR1...
make: *** [Makefile:28: ejercicio3] User defined signal 2


    - si envio sigusr1
    Programa suspendido. Esperando la señal SIGUSR1...
    Señal SIGUSR1 recibida. Programa reanudado.
    Programa reanudado después de recibir SIGUSR1.
*/


#include <stdio.h>
#include <signal.h>

// Función manejadora de señales
void handler_sigusr1(int signo)
{
    // Mostrar mensaje cuando se recibe SIGUSR1
    printf("Señal SIGUSR1 recibida. Programa reanudado.\n");
}

int main() {
    // Configurar manejador de señales para SIGUSR1
    struct sigaction sa;
    sa.sa_handler = handler_sigusr1;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    // Configurar manejador para SIGUSR1
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Error en sigaction");
        return 1;
    }

    // Mostrar mensaje inicial
    printf("Programa suspendido. Esperando la señal SIGUSR1...\n");

    // Configurar la máscara de señales
    sigset_t new_mask, old_mask;
    sigemptyset(&new_mask);
    sigaddset(&new_mask, SIGUSR1);

    // Bloquear SIGUSR1 y guardar la máscara anterior
    sigprocmask(SIG_BLOCK, &new_mask, &old_mask);

    // Suspender el programa hasta que se reciba SIGUSR1
    sigsuspend(&old_mask);

    // Desbloquear SIGUSR1
    sigprocmask(SIG_UNBLOCK, &new_mask, NULL);

    // Después de recibir SIGUSR1, la ejecución continúa aquí
    printf("Programa reanudado después de recibir SIGUSR1.\n");

    return 0;
}


