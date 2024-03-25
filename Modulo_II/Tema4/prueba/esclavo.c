
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>

/*
solo quiero sumar los vectores y devovler el resutlado
*/

int main (int argc, char *argv[]){

    // minimo tengo que ingresar un numero, si no error
	if (argc < 2){
		printf("Uso: %s <num1> <num2> ... <numN>\n", argv[0]);
		return 1;       
	}

    int suma  = 0;  

    for (int i = 1; i < argc; i++){
        suma += atoi(argv[i]);
    }                                   

    // printf("Suma en el esclavo: %d\n", suma);
    // escribimos 
    write(STDOUT_FILENO, &suma, sizeof(int));
    
    return 0;
}       