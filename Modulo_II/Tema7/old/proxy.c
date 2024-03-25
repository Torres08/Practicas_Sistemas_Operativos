/*

    Nombre: Spool de Impresión 
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    proxy, esclavo del servidor 

    - proxy recibe datos del servidor por entrada estandar
    - proxy guarda datos en temporal file, hasta finalizar 
    - proxy imprime por pantall , asegurandose de acceso exclusivo

*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>


void imprimir_exclusivo(const char *datos){
    // 1. abro el archivo temporal
    int fd_temporal; 

    printf("Proxy (%d): Imprimiendo en pantalla. \n", getpid());
    
    if ((fd_temporal = open("./papelera/temporal.txt", O_WRONLY | O_CREAT | O_APPEND, 0666)) < 0){
        perror("Error al abrir el archivo temporal. \n");
        exit(EXIT_FAILURE);
    }

    // 2. escribe los datos en el archivo temporal 
    // datos es el buffer escritura + bytes_leidos
    if (write(fd_temporal, datos, sizeof(datos)) < 0){
        perror("Error al escribir en el archivo temporal. \n");
        exit(EXIT_FAILURE);
    }


    // 3. cierra el archivo temporal 
    close(fd_temporal);

    // 4. imprime por pantalla, asegurandose de acceso exclusivo
    // abro en lectura 

    if ((fd_temporal = open("./papelera/temporal.txt", O_RDONLY)) < 0){
        perror("Error al abrir el archivo temporal. \n");
        exit(EXIT_FAILURE);
    }

    // 5. imprime por pantalla desde el archivo temporal
    char buffer[1024];
    ssize_t bytes_leidos;

    while ((bytes_leidos = read(fd_temporal, buffer, sizeof(buffer))) > 0){
        // escribo en salida estandar
        write(STDOUT_FILENO, buffer, bytes_leidos);
    }


    // 6. cierro y elimino el archivo temporal 
    close(fd_temporal);
    remove("./papelera/temporal.txt");

}

int main(){

    // mensaje inicio
    printf("Proxy (%d): Inicio de ejecucion. \n", getpid());
    
    // 1. buffer escritura + bytes_leidos
    char buffer[1024];
    ssize_t bytes_leidos;


    // 2. lee datos del servidor por entrada estandar 

    while ((bytes_leidos = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0){
        // 3. guarda datos en temporal file
        // 4. imprime por pantalla, asegurandose de acceso exclusivo
        imprimir_exclusivo(buffer);
    }

    return EXIT_SUCCESS;
}