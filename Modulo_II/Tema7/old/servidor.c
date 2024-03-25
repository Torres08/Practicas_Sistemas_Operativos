/*

    Nombre: Spool de Inversion
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    pasos: spool de inversion

        1. el cliente solicita impresion al servidor. fifo_entrada
        2. el servidor recibe solicitud (creaproxy - proceso hijo, funcionalidad en proxy.c, como esclavo) y archivo de bloqueo
        3. el servidor responde al cliente. fifo_salida ¿como nos comunicamos con el proxy -> maestro esclavo?
        4. el cliente lee respuesta
        5. el cliente envia datos al proxy desde fifo_salida (pid)
        6. el proxy guarda datos en temporal file, hasta finalizar el envio por parte del cliente, proxy lee salida y entrada estandar
        7. el proxy imprime en pantalla, asegurandose de tener acceso exclusivo
        8. con sigaction comporbamos en el servidor que no hay procesos zombies, esperamos a que terminen los hijos


*/

#include <stdio.h>     // perror
#include <sys/types.h> // pid_t
#include <sys/stat.h>  // mkfifo, stat
#include <fcntl.h>     // open
#include <stdlib.h>    // exit
#include <signal.h>    // sigaction
#include <unistd.h>    // open, read, write, close

// librerais quickfix para que compile
#include <bits/waitflags.h>
#include <bits/sigaction.h>
#include <asm-generic/signal-defs.h>


// 4. manejador para procesos zombioes -> espera
void manejador_sigchld(int sig)
{
    // 5. espero a que terminen los hijos, -1 espero a cualquiera
    while (waitpid(-1, NULL, WNOHANG) > 0)
        ;
}

// al main no se le pasan argumentos
int main()
{

    // 1. voy a crear los FIFOs con mkfifo, se puede crear tambien con el open, asi mejor
    // lo que le tengo que mandar a cliente es un unico nombre, de forma que los clientes suponen que el 
    // nombre de FIFO concido de entrada al servidor es dicho nobre concatenado
    // con el caracter e, el de salida con caracter s
    mkfifo("fifoe", 0666);
    mkfifo("fifos", 0666);

    // 2. abro los FIFOs con open
    int fifo_entrada = open("fifoe", O_RDONLY);
    int fifo_salida = open("fifos", O_WRONLY);

    // 3. pid _proxy + configurar señal SIGCHILD sigaction
    struct sigaction sa;
    sa.sa_handler = manejador_sigchld;
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    sigaction(SIGCHLD, &sa, NULL); // definir el manejador de señales

    int pid_proxy;

    printf("Copisteria abierta\n");

    // 4. bucle del programa
    while (1)
    {

        // 5. el servidor recibe solicitud del cliente, leo el fifo_entrada
        if (read(fifo_entrada, &pid_proxy, sizeof(int)) > 0)
        {
            printf("Servidor Copisteria: recibida solicitud de impresion del cliente %d\n", pid_proxy);

            // 6. creo el proceso hijo = proxy, envia datos al proxy
            int pid = fork();
            if (pid == 0)
            {
                // ejecutamos el proxy
                printf("Servidor Copisteria: ejecutando proxy ... \n");
                execlp("./papelera/proxy", "proxy", NULL);
                perror("Error al ejecutar el proxy");
                exit(EXIT_FAILURE);
            }
            else if (pid > 0)
            {
                // 7. caso padre, envio datos al proxy
                printf("Servidor Copisteria: Enviando datos al proxy ... %d\n", pid_proxy);
                write(fifo_salida, &pid, sizeof(int));
            }
            else
            {
                perror("Error al leer FIFO de entrada");
                exit(EXIT_FAILURE);
            }
        }
    }

    // cerrar FIFOS antes de salir (nunca se ejecuta en este caso)
    close(fifo_entrada);
    close(fifo_salida);

    return EXIT_SUCCESS;
}
