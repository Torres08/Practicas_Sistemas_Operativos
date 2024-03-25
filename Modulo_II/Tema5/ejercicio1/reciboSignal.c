/*

    Nombre: Ejercicio1
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    Ejercicio 1: Conpila y comprende el programa

    Ejecucion del programa: $> ./envioSignal [012] <PID>

    EStos programas se comunican mediante señales, dependiendo de la señal enviada o recibida 
    el programa acabará haciendo mencion a una señal o a otra
*/

/*
 reciboSignal.c
 Trabajo con llamadas al sistema del Subsistema de Procesos conforme a POSIX 2.10
 Utilización de la llamada sigaction para cambiar el comportamiento del proceso       
 frente a la recepción de una señal.
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

static void sig_USR_hdlr(int sigNum) {
	if(sigNum == SIGUSR1)
    	printf("\nRecibida la senal SIGUSR1\n\n");
    else if(sigNum == SIGUSR2)
    	printf("\nRecibida la senal SIGUSR2\n\n"); 
}


int main(int argc, char *argv[]) {
	
    // 1. para recibir procesar una señal necesito un struct sigaction
    struct sigaction sig_USR_nact;
    
    //2. setvbuf para que no se haga buffering de la salida estandar
    if(setvbuf(stdout,NULL,_IONBF,0)) {
        perror("\nError en setvbuf");
    }

	// 3. Inicializar la estructura sig_USR_na para
    // especificar la nueva acción para la señal.
    // si es terminacion termina, si es 1 hace el mensaje 1 y si hace el mensaje 2 
	sig_USR_nact.sa_handler= sig_USR_hdlr;

	// 4.'sigemptyset' inicia el conjunto de señales dado al conjunto vacio. 
	sigemptyset (&sig_USR_nact.sa_mask);
	
    // 5. Establecer la nueva acción para la señal del proceso., antes usaba SA_RESTART
    sig_USR_nact.sa_flags = 0;

	//5. Establecer mi manejador particular de señal para SIGUSR1
	if(sigaction(SIGUSR1,&sig_USR_nact,NULL)<0) {
		perror("\nError al intentar establecer el manejador de senal para SIGUSR1");
		exit(EXIT_FAILURE);
    }

    //Establecer mi manejador particular de señal para SIGUSR2
	if( sigaction(SIGUSR2,&sig_USR_nact,NULL) <0) {
		perror("\nError al intentar establecer el manejador de senal para SIGUSR2");
		exit(EXIT_FAILURE);
    }
	for(;;)
   	{
   	}
}