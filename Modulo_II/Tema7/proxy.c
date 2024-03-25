#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void imprimir_exclusivo(const char *datos) {
    int fd_temporal;
    printf("Proxy (%d): Imprimiendo en pantalla.\n", getpid());

    if ((fd_temporal = open("./papelera/temporal.txt", O_WRONLY | O_CREAT | O_APPEND, 0666)) < 0) {
        perror("Error al abrir el archivo temporal.");
        exit(EXIT_FAILURE);
    }

    if (write(fd_temporal, datos, strlen(datos)) < 0) {
        perror("Error al escribir en el archivo temporal.");
        exit(EXIT_FAILURE);
    }

    close(fd_temporal);

    if ((fd_temporal = open("./papelera/temporal.txt", O_RDONLY)) < 0) {
        perror("Error al abrir el archivo temporal.");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    ssize_t bytes_leidos;

    printf("hola\n");
    while ((bytes_leidos = read(fd_temporal, buffer, sizeof(buffer))) > 0) {
        printf("hola\n");   
        write(STDOUT_FILENO, buffer, bytes_leidos);
    }

    if ((fd_temporal = open("./papelera/temporal.txt", O_RDONLY)) < 0) {
    perror("Error al abrir el archivo temporal para lectura");
    exit(EXIT_FAILURE);
}

    close(fd_temporal);
}

int main() {
    printf("Proxy (%d): Inicio de ejecucion.\n", getpid());

    char buffer[1024];
    ssize_t bytes_leidos;

    while ((bytes_leidos = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
        imprimir_exclusivo(buffer);
    }

    return EXIT_SUCCESS;
}

