#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>

void manejador_sigchld(int sig) {
    while (waitpid(-1, NULL, WNOHANG) > 0)
        ;
}

int main() {
    mkfifo("fifoe", 0666);
    mkfifo("fifos", 0666);

    int fifo_entrada = open("fifoe", O_RDWR);  // Modo lectura/escritura
    int fifo_salida = open("fifos", O_WRONLY);

    struct sigaction sa;
    sa.sa_handler = manejador_sigchld;
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    sigaction(SIGCHLD, &sa, NULL);

    printf("Copisteria abierta\n");

    while (1) {
        int pid_proxy;
        if (read(fifo_entrada, &pid_proxy, sizeof(int)) > 0) {
            printf("Servidor Copisteria: recibida solicitud de impresion del cliente %d\n", pid_proxy);

            int pid = fork();
            if (pid == 0) {
                // El código del proxy...
                // Asegúrate de que el proxy se está ejecutando correctamente.
                printf("Proxy en proceso %d\n", getpid());
                execlp("./papelera/proxy", "proxy", NULL);
                perror("Error al ejecutar el proxy");
                exit(EXIT_FAILURE);
            } else if (pid > 0) {
                write(fifo_salida, &pid, sizeof(int));
                printf("Servidor Copisteria: Enviando datos al proxy ... %d\n", pid_proxy);
                // Cierra el descriptor de archivo que no necesitas
                close(fifo_salida);
                
            } else {
                perror("Error al leer FIFO de entrada");
                exit(EXIT_FAILURE);
            }
        }
    }

    close(fifo_entrada);
    close(fifo_salida);

    return EXIT_SUCCESS;
}

