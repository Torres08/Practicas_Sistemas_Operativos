/*

    Nombre: tarea9.c Ejemplo de manejador señal SIGINT
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    Tarea 9: ejemplo llamada al sistema sigaction para estrablecer un manejador para la señal SIGINT

    Ejecucion del programa: $> ./Tarea9
*/

#include <stdio.h>
#include <signal.h> // para la llamada al sistema sigaction

int main()
{
    struct sigaction sa;
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);

    // Reiniciar las funciones que hayan sido interrumpidas por un manejador
    sa.sa_flags = SA_RESTART;

    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        printf("error en el manejador");
    }
    while (1)
        ;
    
    return 0;
}