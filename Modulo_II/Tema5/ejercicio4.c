/*

    Nombre: Ejercicio4 Ejemplo de manejador señal SIGINT
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    Ejercicio4: comprer este código 
*/


#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

static int signal_recibida = 0;

static void manejador (int sig) {
	signal_recibida = 1;
}

int main (int argc, char *argv[]) {
    sigset_t conjunto_mascaras;
    sigset_t conj_mascaras_original;
    struct sigaction act;
	
    //Iniciamos a 0 todos los elementos de la estructura act 
    memset(&act, 0, sizeof(act));

    act.sa_handler = manejador;

    if (sigaction(SIGTERM, &act, 0)) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    
    //Iniciamos un nuevo conjunto de mascaras
    sigemptyset(&conjunto_mascaras);
    //Añadimos SIGTERM al conjunto de mascaras
    sigaddset(&conjunto_mascaras, SIGTERM);
    
    //Bloqueamos SIGTERM
    if (sigprocmask(SIG_BLOCK, &conjunto_mascaras, &conj_mascaras_original) < 0) {
       perror ("primer sigprocmask");
       exit(EXIT_FAILURE);
    }

    // Suspender el programa hasta que se reciba SIGUSR1
    //sigsuspend(&old_mask);
    //sleep (100);

    sigsuspend(&conj_mascaras_original);

    // Desbloquear SIGUSR1
    sigprocmask(SIG_UNBLOCK, &conjunto_mascaras, NULL); 

    //Restauramos la señal ó desbloqueamos SIGTERM
    if (sigprocmask(SIG_SETMASK, &conj_mascaras_original, NULL) < 0) {
       perror ("segundo sigprocmask");
       exit(EXIT_FAILURE);
    }

    sleep(1);

    if (signal_recibida)
   		printf ("\nSenal recibida\n");
   	exit(EXIT_SUCCESS);
}