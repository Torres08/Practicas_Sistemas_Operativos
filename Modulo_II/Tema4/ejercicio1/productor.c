/*

    Nombre: Ejercicio1.c Productor y Consumidor
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    Ejercicio 2: ¿Qué hace el siguiente programa?, Consulte en el manual las llamadas al sistema para la creacion de archivos especiales
    en general mknod y la especifica para archivos FIFO mkfifo. Compile y ejecute el programa sobre productor/consumidor, usa como
    mecanismo de comunicacion un cauce FIFO. Determine en qué orden y manera se han de ejecutar los dos programas para su correcto
    funcionamiento y como queda reflejado en el sistema que estamos utilizando un cauce FIFO Justifica tu respuesta

    Ejecucion del programa: $> ./productor
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define ARCHIVO_FIFO "./papelera/ComunicacionFIFO"

int main(int argc, char *argv[])
{
    int fd;

    // 5. Comprobar el uso correcto del programa, paso un mensaje con la cadena al final fin , envio un mensaje
    if (argc != 2)
    {
        printf("\nproductorFIFO: faltan argumentos (mensaje)");
        printf("\nPruebe: productorFIFO <mensaje>, donde <mensaje> es una cadena de caracteres.\n");
        exit(EXIT_FAILURE);
    }

    // 6. Intentar abrir para escritura el cauce FIFO
    if ((fd = open(ARCHIVO_FIFO, O_WRONLY)) < 0)
    {
        perror("\nError en open");
        exit(EXIT_FAILURE);
    }

    // 7. Escribir en el cauce FIFO el mensaje introducido como argumento solo hacer el write fd, mensaje, tamaño del mensaje + 1
    if ((write(fd, argv[1], strlen(argv[1]) + 1)) != strlen(argv[1]) + 1)
    {
        perror("\nError al escribir en el FIFO");
        exit(EXIT_FAILURE);
    }

    // 8. cierre del descriptor
    close(fd);
    return EXIT_SUCCESS;
}
