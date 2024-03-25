/*

    Nombre: tarea10.c Ejemplo de manejador señal SIGINT
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    Tarea 10: ejemplo llamada al sistema sigaction para estrablecer un manejador para la señal SIGINT, con un manejador propio

    Ejecucion del programa: $> ./Tarea10
*/

#include <stdio.h>
#include <signal.h>

// 6. mi manejador lleva un contador de veces que se ha recibido la señal, si es > 3 termina el bucle y termina la app, tiene ademas un print
static int s_recibida = 0;
static void handler(int signum)
{
    printf("\n Nueva accion del manejador \n");
    s_recibida++;
}

int main()
{
    // 1. para manejar señales creo struct signaction
    struct sigaction sa;

    // 2. asigno el manejador, manejador indica que sucede cuando ocurre dicha señal
    sa.sa_handler = handler; // ignora la se–al
    
    // 3. Inicializa el conjunto de señales bloqueadas durante la ejecucion del manejador
    sigemptyset(&sa.sa_mask);

    // 4. Reiniciar las funciones que hayan sido interrumpidas por un manejador
    sa.sa_flags = SA_RESTART;


    // 5. Llamada al sistema sigaction, configura la accion de señal para reiniciar funciones que hayan sido interrumpidas por el manejador
    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        printf("error en el manejador");
    }


    // /6 mi manejador lleva un contador de veces que se ha recibido la señal, si es > 3 termina el bucle y termina la app
    while (s_recibida < 3)
        ;
}