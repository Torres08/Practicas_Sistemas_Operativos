/*

    Nombre: Ejercicio1.c
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    Ejercicio 2: implementa un programa que realice la siguiente funcionalidad. El programa acepta como argumento el nombre de un archivo (pathname), 
    lo abre y lo lee en bloques de tamaño 80 Bytes, y crea un nuevo archivo de salida, salida.txt, 
    en el que debe aparecer la siguiente información:

        Bloque 1:
        // Aqui van los primeros 80 Bytes del archivo pasado como argumento
        Bloque 2:
        // Aqui van los siguientes 80 Bytes del archivo pasado como argumento
        ...
    
    si no se pasa un argumento al programa se debe utilizar la entrada estandar como archivo de entrada 
    

    modificacion adicional: ¿Cómo tendrias que modificar el programa para que una vez finalizada
    la escritura en el archivo de salida y antes de cerrarlo, pudiesemos indicar en su primera
    linea el numero de la etiqueta "Bloque i" escritas de forma que tuviese la siguiente aparencia?

        EL numero de bloques es <n bloques>
        Bloque 1:
        // Aqui van los primeros 80 Bytes del archivo pasado como argumento
        Bloque 2:
        // Aqui van los siguientes 80 Bytes del archivo pasado como argumento
        ... 
    
    Ejecucion del programa: $> ./ejercicio2 <nombre_archivo>   
                            $> ./ejercicio2

*/

#include <fcntl.h> // funciones de control de ficheros (open, write, lseek, close)
#include <stdio.h> // libreria estandar de entrada y salida
#include <errno.h> // manejo de errores
#include <sys/stat.h>  // necesario con fctnl.h
#include <sys/types.h> // necesaria con fctnl.h
#include <stdlib.h> // EXIT FAILURE 
#include <unistd.h> // STDIN_FILENO
#include <string.h> // strlen


int main (int argc, char *argv[]){

    // 1. creo fd_in y el fd_out, buffer de 80 bytes, label de 20 bytes y salto de linea
    int fd_in, fd_out;
    char buffer[80];
    char label[20];
    char salto[] = "\n";

    if (argc < 2){
        // 2. caso en el que no de un fichero escribo por terminal
        fd_in = STDIN_FILENO;
    } else {
        // 3. caso en el que de un fichero lo abro
        if ((fd_in = open(argv[1], O_RDONLY)) < 0){
            perror("\nError en open");
            exit(EXIT_FAILURE);
        }
    }

    // 4. creo el fichero de salida
    if ((fd_out = open("salida.txt", O_CREAT|O_TRUNC|O_WRONLY, 0666)) < 0){
        perror("\nError en open");
        exit(EXIT_FAILURE);
    }

    int contador = 0;
    int longitud;

    // modificacion adicional: añado numero de bloques usados

    // 11. leo el fichero como antes pero no escribo nada, solo para contar los bloques
    while ((longitud = read(fd_in, buffer, 80)) > 0){
        contador++;
    }
    // 12. cuando he leido tengo que cerrar el fichero
    close(fd_in);

    // 13. creo el buffer donde voy a escribir el numero de bloques
    char totalBloques[50];
    sprintf(totalBloques, "Numero total de bloques: %d\n", contador);
    if (write(fd_out, totalBloques, strlen(totalBloques)) < 0){
        perror("\nError en write totalBloques");
        exit(EXIT_FAILURE);
    }

    // 14. volvemos a abrir fd_in y volvemos a empezar, reiniciamos ademas el contador
    if ((fd_in = open(argv[1], O_RDONLY)) < 0){
            perror("\nError en open");
            exit(EXIT_FAILURE);
    }
    contador = 0;
    
    
    // 5. leo el fichero de entrada en bloques de 80 bytes
    while ((longitud = read (fd_in, buffer, 80)) > 0){
        contador ++;
        // 6. creo la etiqueta
        sprintf(label, "Bloque %d:\n", contador);

        // 7. escribo la etiqueta en el fichero de salida
        if (write(fd_out, label, strlen(label)) < 0){
            perror("\nError en write laber");
            exit(EXIT_FAILURE);
        }

        // 8. escribo el bloque de 80 bytes en el fichero de salida 
        if (write (fd_out, buffer, longitud) < 0){
            perror("\nError en write buffer");
            exit(EXIT_FAILURE);
        }

        // 9. escribo el salto de linea en el fichero de salida
        if (write (fd_out, salto, strlen(salto)) < 0){
            perror("\nError en write salto");
            exit(EXIT_FAILURE);
        }

        
    }

    

    // 10. cierro los ficheros
    close(fd_in);
    close(fd_out);
}   


