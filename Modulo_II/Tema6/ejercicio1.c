
/*

	Nombre: Ejercicio2. Contador
	Autores: Torres Ramos, Juan Luis
	Sistemas Operativos

	Ejercicio 2: IMplementa un programa que admita t argumentos . El primer argumeto sera una orden de Linux, segundo
	< o > y el tercero el nombre de un archivo (puede existir o no) Programa ejecutara la orden que se especifica como
	un argumento primero, y luego redirigira la entrada o salida estandar segun el segundo argumento hacia el archivo indicado en el tercer
	argumento , < y > tienen que ir entre comillas

	Ejecucion del programa: ./ejercicio1 sort "<" temporal

*/

/*
 * Ejercicio 1
 * Torres Ramos, Juan Luis
 *
 * Sesion 6: control de archivos y archivos proyectados a memoria
 *
 * sesion 6 parte 1
 *
 * funcion fcntl (dup, dup2)
 * 	cambiar o consultar las banderas de control de acceso de aun archivo abierto
 *
 * lo unico de la parte II, hay ejercicios con archivos proyectado a memoria, ver y entender codigo, nada mas
 *
 * hacer ejercicio 1, pasamos una orden de linux, operador < o >, y luego un fichero, si no existe se crea, redirigira segun < o > , ls > temporal,
 * orden +
 *
 * programa ejecuta la orden que se especifica como argumento primero
 *
 * ./mi_programa sort "<" temporal
 *
 * < es entre comillas para que el shell no se confundia con una redireccion
 *
 * podemos usar dup/dup2, el fcntl.h -> imprtante para cerrojos
 *
 * principio asumo que no existe el archivo
 *
 * < redireccion de entrada
 *	- si no existe archivo se crea, si no se sobreescribe
 * > redireccion de salida
 * 	- si el archivo no existe, error y el comando falla
 * 	- pongo el error o creo el archivo
 */

/*
	sort < archivo.txt
		ordena lineas de un archivo
	
	sort > archivo.txt
		toma el contenido de archivo.txt muestra salida ordenada en la consola

*/

/*

texto desordenado
	gato
	perro
	manzana
	zanahoria
	elefante
	uva


texto ordenado 
	elefante
	gato
	manzana
	perro
	uva
	zanahoria


*/

/*
lo hago con ls, es mas comodo, sort no se por que el > no funciona, se cuelga 

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // libreria para fctnl
#include <fcntl.h>	// libreria para fcntl

int main(int argc, char *argv[])
{

	// 1. comporbamos argumentos, tenemos que pasar
	if (argc != 4)
	{
		perror("Error en el numero de argumentos. \nUso correcto: ./ejercicio1 orden \"<\" o \">\" <archivo> \n");
		exit(EXIT_FAILURE);
	}

	// 2. creo el descriptor fd
	int fd;

	// 3. caso redireccion de entrada
	// para cuando introducimos un "<" el archivo esta creado
	if (strcmp(argv[2], "<") == 0)
	{											// compruebo la cadena de caracteres, COMPARO CON STRCMP
		fd = open(argv[3], O_RDONLY | O_CREAT); // Abrimos el archivo que sera la STDIN
		close(STDIN_FILENO);					// cerramos  la STDIN verdadera, la estandar
		fcntl(fd, F_DUPFD, STDIN_FILENO);		// se coloca la creada en lugar de la estandar
		execlp(argv[1], argv[1], NULL);
	}

	// 4.redireccion de salida
	// para cuando introducimos ">" se crea el archivo
	else if (strcmp(argv[2], ">") == 0)
	{														  // compruebo la cadena de caracteres
		fd = open(argv[3], O_RDWR | O_CREAT | O_TRUNC, 0664); // creamos el archivo, 0664 permisos del archiv
		close(STDOUT_FILENO);								  // cerramos  la STDIN verdadera, la estandar, como si fuese 1
		fcntl(fd, F_DUPFD, STDOUT_FILENO);					  // se coloca la creada en lugar de la estandar
		execlp(argv[1], argv[1], NULL);						  // ejecutamos la orden
	}
	else
	{
		printf("Error en el segundo argumento, tiene que ser \"<\" o \">\", entre comillas");
		exit(-1);
	}

	close(fd); // cerramos el descriptor al final
	return 0;
}
