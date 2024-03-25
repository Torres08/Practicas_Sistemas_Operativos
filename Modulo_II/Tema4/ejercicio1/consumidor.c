/*

    Nombre: Ejercicio1.c Productor y Consumidor
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    Ejercicio 1: ¿Qué hace el siguiente programa?, Consulte en el manual las llamadas al sistema para la creacion de archivos especiales
    en general mknod y la especifica para archivos FIFO mkfifo. Compile y ejecute el programa sobre productor/consumidor, usa como
    mecanismo de comunicacion un cauce FIFO. Determine en qué orden y manera se han de ejecutar los dos programas para su correcto
    funcionamiento y como queda reflejado en el sistema que estamos utilizando un cauce FIFO Justifica tu respuesta

    Ejecucion del programa: $> ./consumidor &, ./productor <mensaje> 
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <linux/stat.h>
#include <signal.h>
#define ARCHIVO_FIFO "./papelera/ComunicacionFIFO"

int main(void)
{
    // 1. creo un descriptor para el archivo FIFO, con un buffer de 80 bytes donde estara el mensaje a leer, leidos es el numero de bytes leidos
    int fd;
    char buffer[80]; // Almacenamiento del mensaje del cliente.
    int leidos;

    // 2. Crear el cauce con nombre (FIFO) si no existe, umask(0) para que no se aplique la mascara de creacion de archivos por defecto
    umask(0);
    //mknod(ARCHIVO_FIFO, S_IFIFO | 0666, 0);
    mkfifo(ARCHIVO_FIFO, 0666); // otra version para crear el cauce/archivo

    // 3. Abrir el cauce para lectura-escritura
    if ((fd = open(ARCHIVO_FIFO, O_RDWR)) < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // 4. bucle infinito, Aceptar datos a consumir hasta que se envie la cadena fin, cuando eso hace un close y return indicando que ha finalizado
    // recibe el mensaje del productor y lo muestra por pantalla
    while (1)
    {
        leidos = read(fd, buffer, 80);
        if (strcmp(buffer, "fin") == 0)
        {
            printf("\nEl consumidor ha terminado\n");
            close(fd);
            kill(getpid(), SIGTERM); // Envía la señal SIGTERM al proceso actual para terminarlo, no es del ejercicio pero lo añado, lo vemos luego
            return EXIT_SUCCESS;
        }
        printf("\nMensaje recibido: %s\n", buffer);
    }

    return EXIT_SUCCESS;
}