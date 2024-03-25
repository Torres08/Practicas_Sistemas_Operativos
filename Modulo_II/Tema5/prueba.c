/*
 * Ejercicio 5
 *
 * Torres Ramos, Juan Luis
 *
 * Gestion de señales, utilizar metodos de la biblioteca signal : kill sigaction, sigpromask, 
 *
 * llevar bien la 1 y 2 sesion, recorrer ficherros escribir y lleer , hijos y pipes/cauces, sesion 1 y sesio 4 las mas importantes
 * 
 * revision /prueba: tarea 9 y tarea 10, ejercicio1 (envio/recibo de sign0, kill sigaction)
 *
 * terminal ./pregron&
 * [1] 5824
 *
 * terminal kill -2   
 *
 * Tipo ejercicio 2: crea un contador tal que cada vez que cada vez que reciba una señal que se
 * pueda manejar, muestre por pantalla la señal y el numero de veces que se ha recibido ese tipo
 * de señal , y un mensaje inicial indicando las señales que no puede manejar. En el cuadro
 * del pdf muestra un ejemplo de la ejecucion del programa
 * 
 * igual que el ejercicio 2 
 *
 * $ ./ejercicio5 &
 * [2] 1899
 *
 * kill .cont 1899
 * la señal 18 se ha recibido 1 vez
 */

// hay que saberse las librerias para el examen

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>

/*
 * creamos un buffer para contar el numero de veces que se a recibido 
 * la seña i-esima y por otro lado saber si la señal i-esima es una 
 * señal manejable o no 0=true, 1=false
 *
 */


//buffer señales validas, la 0 no se usa
static int count_signals[65]={0};

//buffer señales invalidas
static int invalid_signals[65]={0};

// manejador
static void manejador(int sigNum){

	printf("%d", sigNum);
	// para las señales que no puede manejar va de 0 a 64
	if (sigNum > 64 || sigNum < 0){
		printf("El programa no puede capturar la señal %d", sigNum);
		kill(getpid(),SIGSTOP); // matamos el proceso, 
	}

	if (invalid_signals[sigNum] == 0){
		count_signals[sigNum]++;
		printf("La señal %d se ha recibido %d veces.\n",sigNum, count_signals[sigNum]);
	} else {
		printf("La señal es invalida %d", sigNum);
		kill(getpid(), SIGSTOP);
	}

}


#include <stdio.h>

int main(int argc, char *argv[]) {
    
    //necesitamos este struct para operar el manejador
    struct sigaction sa;

    //OLDACT lo dejamos a nulo
    //comprobamos el buffer
    if (setvbuf(stdout, NULL,_IONBF,0)){
	    perror("Error en el servbuff\n");
    }

    // inicializamos la estructura que maneja al operador para especificar la nueva accion para el
    // tenemos que definir nuestro manejador
    sa.sa_handler = manejador;

    // sigemptyset -> inicio el conjunto de señales a partir conjunto vacio
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    int i; // contador para los bucles 

    for (i=0; i <65; i++){
	if(sigaction(i,&sa,NULL)<0){
		printf("No puedo manejar la señal %d\n", i);
		invalid_signals[i] = 1;
	}

    }

    printf("Esperndo envio de señales .... \n");
    while(1);
}



