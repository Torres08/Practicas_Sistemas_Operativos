/*

    Nombre: Ejercicio1.c Productor y Consumidor
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    Ejercicio 2: consulte en el manual la llamad aal sistema pipe. Pruebe a ejecutar el siguiente programa que utiliza un
    cauce sin nombre y describa la funcion que realiza

    Ejecucion del programa: $> ./ejercicio2
*/

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{

    // 1. para cauces sin nombres necesitare array descriptores de ficheros, un array de dos elementos, uno para la lectura y otro para la escritura
    // tmb lo del PID 
    int fd[2], numBytes;
    pid_t PID;
    char mensaje[] = "\nEl primer mensaje transmitido por un cauce!!\n";
    char buffer[80];

    // 2. creo el cauce sin nombre, el array de dos elementos, uno para la lectura y otro para la escritura 
    pipe(fd); 


    // 3. creo el proceso hijo
    if ((PID = fork()) < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (PID == 0)
    {
        // 4. caso hijo 
        // quiero escribir asi que tengo que cerrar primero el letura y luego usar el descriptor de escritura

        // Cierre del descriptor de lectura en el proceso hijo
        close(fd[0]);
        // Enviar el mensaje a traves del cauce usando el descriptor de escritura
        write(fd[1], mensaje, strlen(mensaje) + 1);
        exit(EXIT_SUCCESS);
    }
    else
    { 
        //5. caso padre Estoy en el proceso padre porque PID != 0
        // en el padre hare lo contrario del hijo, leere los mensajes, por lo que cierro el descriptor de escritura y leo con el de lectura

        // Cerrar el descriptor de escritura en el proceso padre
        close(fd[1]);

        // Leer datos desde el cauce.
        // numBytes debera ser 80, el tamaño del buffer
        numBytes = read(fd[0], buffer, sizeof(buffer));

        // devuelve 47 porque el mensaje es 46 y luego le usmo 1para incluir el caracter nulo '\0'
        printf("\nEl numero de bytes recibidos es: %d", numBytes);
        printf("\nLa cadena enviada a traves del cauce es: %s", buffer);
    }

    return EXIT_SUCCESS;
}
