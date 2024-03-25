/*
 *	Ejercicio 0: Contar numero archivos regulares en un directorio dado y mostrar resultado
 *	Torres Ramos, Juan Luis
 *
 *	./ejercicio0 <path_dir> <n_entero>
 *
 *	usamos el path de prueba que hemos creado para testear
 *
 * 	Pasos
 * 		0. comporbar que se pasan los argumentos correctos
 *		1. abrir directorio path
 *		2. detectar archivos regulares
 *		3. "Mi numero es <n_entero> archivos regulares" escribirlo en los archivos detectad *		       os
 *	
 *	Modificaciones
 *		4. abrir archivos -> O_TRUNC -> 0_APPEND (cambiarlo por append)
 *		   mostrar contenido anterior del archivo y agregar la nueva linea
 *
 */

#include <stdio.h> // funciones entrada y salida (printf)
#include <stdlib.h> // incluye funciones como atoi (convierte una cadena a un entero) 
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
	
	// 0.Comprobar que se pasan los argumentos correctos, y declaro sus variables
	if (argc != 3){
		printf("ERROR USO \n Uso: %s <path_dir> <n_entero>\n", argv[0]);
		return 1;
	}
	
	const char *path = argv[1];
	int n_entero = atoi(argv[2]);
	int contador_archivos_regulares = 0;
	

	// 1. Abrir directorio path
	
	DIR *dir = opendir(path);
	if (dir == NULL) {
		// Imprime el tipo de error al abrir, por ejemplo: no such file
		perror("Error al escribir el archivo");
		return 1;
	}
	
	// 2. detecto los archivos regulares con el while
	// representa una entrada de directorio (archivo o subdirectorio)
	struct dirent *entry;

	while ((entry = readdir(dir)) != NULL){
		// si no es null es un archivo
		contador_archivos_regulares++;


		// 3. escribir el mensaje en cada archivo regular
		// snprint permite escribir un mensaje en un buffer
		char buffer[100];
		snprintf(buffer, sizeof(buffer), "Numero ingresado en el argumento: %d\n", n_entero);	
		
		// necesito el path del archivo y abrirlo abrir el archivo 
		
		char path_archivo[1024];
		snprintf(path_archivo, sizeof(path_archivo),"%s/%s", path, entry->d_name);

		int fd = open(path_archivo, O_WRONLY | O_CREAT | O_TRUNC);

		// escribir el archivo
		if (write(fd, buffer, strlen(buffer)) == -1){
			perror("Error al escribir en el archivo");
			return 1;
		}

	}

	// cuando hacemos un opendir tenemos que hacer un closedir
	closedir(dir);
	
	// conteo numero de archivos regulares de un directorio
	printf("Numero total de archivos regulares en %s : %d\n", path, contador_archivos_regulares);

	return 0;
}
