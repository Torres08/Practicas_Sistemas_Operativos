/*

    Nombre: Ejercicio1.c
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    Ejercicio 1: ¿Qué hace el siguiente programa? Probad tras la ejecucion del programa las siguientes ordenes shell
    
	$>cat archivo
		abcdefghijABCDEFGHIJ

	$> od -c archivo
		0000000   a   b   c   d   e   f   g   h   i   j  \0  \0  \0  \0  \0  \0
		0000020  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0
		0000040  \0  \0  \0  \0  \0  \0  \0  \0   A   B   C   D   E   F   G   H
		0000060   I   J
		0000062	

	programa escribe archivo con 10 bytes del buffer buf1 = abcdefghij, desplaza 40 bytes desde el inicio del archivo y escribe 10 bytes del buffer buf2 = ABCDEFGHIJ en el archivo desde el offset anterior estrablecido

	Ejecucion del programa: $> ./ejercicio1
	
*/

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>  	/* Primitive system data types for abstraction\
			   of implementation-dependent data types.
			   POSIX Standard: 2.6 Primitive System Data Types
			   <sys/types.h>
			*/
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>

char buf1[]="abcdefghij";
char buf2[]="ABCDEFGHIJ";

int main(int argc, char *argv[])
{

// 1. creacion file desciptor    
int fd;

// 2. apertura de archivo, si no existe lo crea, si existe lo trunca y lo abre en modo escritura, permisos de lectura y escritura para el usuario
if( (fd=open("archivo",O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR))<0) {
	printf("\nError %d en open",errno);
	perror("\nError en open");
	exit(EXIT_FAILURE);
}

// 3. escritura de 10 bytes del buffer buf1 = abcdefghij en el archivo
if(write(fd,buf1,10) != 10) {
	perror("\nError en primer write");
	exit(EXIT_FAILURE);
}

// 4. desplazamiento de 40 bytes desde el inicio del archivo
if(lseek(fd,40,SEEK_SET) < 0) {
	perror("\nError en lseek");
	exit(EXIT_FAILURE);
}

// 5. escritura de 10 bytes del buffer buf2 = ABCDEFGHIJ en el archivo desde el offset anterior estrablecido
if(write(fd,buf2,10) != 10) {
	perror("\nError en segundo write");
	exit(EXIT_FAILURE);
}

return EXIT_SUCCESS;
}
