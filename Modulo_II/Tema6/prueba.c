
/*
 * Ejercicio 2 - clase
 *
 * Manejo argumentos argv
 *
 * Apertura de fichero (open)
 *
 * Configurar cerrojo (struct flock) (l_type, l_whence, l_start, l_len, l_pid)
 *
 * - Establecer un cerrojo en modo escritura (F_WRLCK)
 * - Llamar fcntl
 *
 *  verificar existencia fichero (stat)
 *
 *  -> escribir PID en fichero (reservar memoria, escritura )
 *
 *  añadir espera (sleep. fgetc)
 *
 *  cierre fichero y liberar (unlink)
 *
 *  ./ejercicio4 <fichero>
 *
 */



#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso correcto: %s <fichero>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // 1. abirmos el archivo con open
    int fd;

    // 2. permisos de lectura y escritura par aadmin, user y groups
    fd = open (argv[1], O_CREAT|O_RDWR, 0666);


    // 3. configurar cerrojo
    struct flock cerrojo;

    cerrojo.l_type = F_WRLCK; // cerrojo de escritura
    cerrojo.l_whence = SEEK_SET;
    cerrojo.l_start = 0;
    cerrojo.l_len = 0; // cerrojo todo el archivo
    cerrojo.l_pid = getpid(); // pid
			
    // 4. establecer cerrojo en modo escritura 
    fcntl (fd,F_SETLK, &cerrojo);

    // 5. verifico existencia fichero stat
    struct stat st;

    stat(argv[1], &st);

    // 6. escribir PID en el archivo
    dprintf(fd, "Mi PID es: %d\n", getpid());

    // 7. añadir espera
    sleep(100);

    // 8. liberar cerrojo, al finalizar el trabajo 
    cerrojo.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW, &cerrojo);

    close(fd);

    // eliminar el archivo quita el link
    unlink(argv[1]);
    return 0;

}
