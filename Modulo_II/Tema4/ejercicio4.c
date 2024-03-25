/*

    Nombre: Ejercicio3.c Productor y Consumidor
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    Ejercicio 3: redirigiendo las entradas y salidas estandares de los procesos a los
    cauces podemos escribir un programa en lenguaje C que permita comunicar órdenes existentes sin
    necesidad de reprogramarlas, tal y como lo hace el shell. EN perticular,
    ejecute el siguiente programa que ilustra la comunicacion entre proceso padre e hijo a través
    de un cauce sin nombre redirigiendo la entrada estandar y la
    salida estandar del padre y el hijo respectivamente

    Ejecucion del programa: $>
*/

#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main(int argc, char *argv[])
{
int fd[2];
pid_t PID;

pipe(fd); // Llamada al sistema para crear un pipe

if ( (PID= fork())<0) {
	perror("\Error en fork");
	exit(EXIT_FAILURE);
}
if (PID == 0) { // ls
	//Cerrar el descriptor de lectura de cauce en el proceso hijo
	close(fd[0]);

	//Duplicar el descriptor de escritura en cauce en el descriptor
	//correspondiente a la salida estandr (stdout), cerrado previamente en
	//la misma operacion
	dup2(fd[1],STDOUT_FILENO);
	execlp("ls","ls",NULL);
}
else { // sort. Proceso padre porque PID != 0.
	//Cerrar el descriptor de escritura en cauce situado en el proceso padre
	close(fd[1]);

	//Duplicar el descriptor de lectura de cauce en el descriptor
	//correspondiente a la entrada est�ndar (stdin), cerrado previamente en
	//la misma operaci�n
	dup2(fd[0],STDIN_FILENO);
	execlp("sort","sort",NULL);
}

return EXIT_SUCCESS;
}
