/*

    Nombre: Ejercicio4
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    Ejercicio 4: Construir un programa que se asegure que solo hay una instancia de el en ejecucion en un momento dado. EL programa, una vez establecido el mecanismo para asegurar que solo una instancia se ejecutara, entrara en un bucle infinito que nos permita comprobar que
    no podemos lanzar más ejecuciones del mismo.En la construccion del mismo, debemos asegurarnos de que el archivo a bloquear no contiene incialmente nada escrito en una ejecucion  anterior del programa

    intenta bloquar archivo lockfile.txt. Si hay otra instancia del programa en ejecucion, simploemente imprime un mensaje y sale
    tambien verifica si el archivo ya contiene datos , en cuyo caso tambien sale 
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>

int main() {
    // 1. Intentamos abrir un archivo 
    int fd = open("./papelera/lockfile.txt", O_RDWR | O_CREAT, 0666);

    if (fd == -1) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    // 2. Intentamos bloquear el archivo con flock
    if (flock(fd, LOCK_EX | LOCK_NB) == -1) {
        printf("Otra instancia ya está en ejecución. Saliendo...\n");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Comprobamos si el archivo ya tenía contenido
    char buffer[1];
    if (read(fd, buffer, sizeof(buffer)) > 0) {
        printf("El archivo ya contenía datos. Saliendo...\n");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Si llegamos aquí, somos la única instancia en ejecución y el archivo está limpio

    printf("Instancia única en ejecución. Entrando en el bucle infinito...\n");

    // Colocamos un caracter en el archivo para indicar que ya estamos en ejecución
    write(fd, "*", 1);

    // Entramos en un bucle infinito para simular la ejecución continua del programa
    while (1) {
        // Hacer tareas aquí
        usleep(1000000); // Espera 1 segundo (puedes ajustar el tiempo según tus necesidades)
    }

    // Nunca deberíamos llegar aquí
    return 0;
}
