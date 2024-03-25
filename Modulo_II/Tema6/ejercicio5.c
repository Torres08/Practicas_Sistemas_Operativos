/*

    Nombre: Ejercicio5. trabajo con archivos proyectados
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    Ejercicio 5: escribe un programa , similar a la orden cp, que utilice para su implementacion la llamada al sistema mmap
    y una funcion de C que nos permite copiar memoria, como por ejemplo memcpy. Para conocer el tamaño del archivo de orgen podemos
    utilizar stat y para establecer el tamaño del archivo destino se puede usar ftruncate.

    Ejecucion del programa: ./ejercicio2 

*/


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>

void copy_file(const char *source_filename, const char *dest_filename) {
    int source_fd = open(source_filename, O_RDONLY);
    if (source_fd == -1) {
        perror("Error al abrir el archivo de origen");
        exit(EXIT_FAILURE);
    }

    struct stat source_stat;
    if (fstat(source_fd, &source_stat) == -1) {
        perror("Error al obtener información del archivo de origen");
        close(source_fd);
        exit(EXIT_FAILURE);
    }

    int dest_fd = open(dest_filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (dest_fd == -1) {
        perror("Error al abrir o crear el archivo de destino");
        close(source_fd);
        exit(EXIT_FAILURE);
    }

    if (ftruncate(dest_fd, source_stat.st_size) == -1) {
        perror("Error al establecer el tamaño del archivo de destino");
        close(source_fd);
        close(dest_fd);
        exit(EXIT_FAILURE);
    }

    char *source_data = (char *)mmap(NULL, source_stat.st_size, PROT_READ, MAP_PRIVATE, source_fd, 0);
    if (source_data == MAP_FAILED) {
        perror("Error al mapear el archivo de origen");
        close(source_fd);
        close(dest_fd);
        exit(EXIT_FAILURE);
    }

    char *dest_data = (char *)mmap(NULL, source_stat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, dest_fd, 0);
    if (dest_data == MAP_FAILED) {
        perror("Error al mapear el archivo de destino");
        munmap(source_data, source_stat.st_size);
        close(source_fd);
        close(dest_fd);
        exit(EXIT_FAILURE);
    }

    memcpy(dest_data, source_data, source_stat.st_size);

    munmap(source_data, source_stat.st_size);
    munmap(dest_data, source_stat.st_size);

    close(source_fd);
    close(dest_fd);

    printf("Archivo copiado exitosamente de %s a %s\n", source_filename, dest_filename);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <archivo_origen> <archivo_destino>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    copy_file(argv[1], argv[2]);

    return EXIT_SUCCESS;
}
