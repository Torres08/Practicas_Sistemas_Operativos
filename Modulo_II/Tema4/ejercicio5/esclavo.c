/*

    Nombre: Ejercicio5.c Maestro y esclavo
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    Ejercicio 5: programa sencillo para calcular y devolver los numeros primos de un intervalo dado por argumento

    Ejecucion del programa: $> ./escalo 5 10    
*/



#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char **argv) {
	if ( argc != 3 ) {
		perror("Fallo argumentos\n");
        exit(EXIT_FAILURE);
	}
	
	setvbuf(stdout,NULL,_IONBF,0);

	int min, max, primo;
	int es_primo; // esto es un bool
	
	min = atoi(argv[1]);
	max = atoi(argv[2]);
	
	// cálculo de primos
	for ( int n = min; n <= max; n++ ) {
		es_primo = 1;
		for ( int k = 2; k*k <= n && es_primo != 0; k++ ) {
			if ( n % k == 0 ) {
				es_primo = 0;
			}
		}
		if ( es_primo != 0 ) {
			//printf("%d\n", n); // no se por que no hace el print sin mas 
            write(STDOUT_FILENO, &n, sizeof(int));
		}
	}
	
	return 0;
}