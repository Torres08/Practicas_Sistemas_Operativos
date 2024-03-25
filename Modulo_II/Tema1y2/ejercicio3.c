/*

	Nombre: Ejercicio3.c
	Autores: Torres Ramos, Juan Luis
	Sistemas Operativos

	Ejercicio 3: ¿Qué hace el siguiente programa?

	Ejecucion del programa: $> ./ejercicio3 <nombre_archivo1>    <nombre_archivo2> ... <nombre_archivoN>

*/

#include <unistd.h> /* POSIX Standard: 2.10 Symbolic Constants <unistd.h>
		     */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> /* Primitive system data types for abstraction	\
			   of implementation-dependent data types.
			   POSIX Standard: 2.6 Primitive System Data Types
			   <sys/types.h>
		       */
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{

	// 1. creo variable stat y un buffer char de 30 bytes
	int i;
	struct stat atributos;
	char tipoArchivo[30];

	// 2. compruebo que se pasa un argumento
	if (argc < 2)
	{
		printf("\nSintaxis de ejecucion: tarea2 [<nombre_archivo>]+\n\n");
		exit(EXIT_FAILURE);
	}

	// 3. para cada argumento pasado como argumento
	for (i = 1; i < argc; i++)
	{

		// 4. nombre del archivo
		printf("%s: ", argv[i]);

		// 5. obtengo los atributos del archivo con la llamada al sistema lstat
		if (lstat(argv[i], &atributos) < 0)
		{
			printf("\nError al intentar acceder a los atributos de %s", argv[i]);
			perror("\nError en lstat");
		}
		else
		{

			// 6. obtengo el tipo de archivo, segun la salida de lstat me da un tipo de archivo u otro, uso macros POSIC para diferenciarlos y los guardo en tipoArchivo con strcpy
			if (S_ISREG(atributos.st_mode))
				strcpy(tipoArchivo, "Regular");
			else if (S_ISDIR(atributos.st_mode))
				strcpy(tipoArchivo, "Directorio");
			else if (S_ISCHR(atributos.st_mode))
				strcpy(tipoArchivo, "Especial de caracteres");
			else if (S_ISBLK(atributos.st_mode))
				strcpy(tipoArchivo, "Especial de bloques");
			else if (S_ISFIFO(atributos.st_mode))
				strcpy(tipoArchivo, "Tuberia con nombre (FIFO)");
			else if (S_ISLNK(atributos.st_mode))
				strcpy(tipoArchivo, "Enlace relativo (soft)");
			else if (S_ISSOCK(atributos.st_mode))
				strcpy(tipoArchivo, "Socket");
			else
				strcpy(tipoArchivo, "Tipo de archivo desconocido");

			// 7. imprimo el tipo de archivo
			printf("%s\n", tipoArchivo);
		}
	}

	return EXIT_SUCCESS;
}
