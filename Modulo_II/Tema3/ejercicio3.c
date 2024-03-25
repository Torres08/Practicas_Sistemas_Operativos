/*

    Nombre: Ejercicio3.c
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    Ejercicio 2: ¿Qué hace el siguiente programa?, comprueba las dos jerarquias, genera 20 procesos en cada una, haz una jerarquia que sea secuancial padre, hijo

    Ejecucion del programa: $> ./ejercicio3
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
    int num_procesos = 20;
    pid_t PID;

    /*
    // 1. creo la jerarquia de procesos 1
    // bucle de 20 procesos
    // proceso padre crea un proceso hijo, y este un nuevo hijo suyo, asi sucesivamente
    // con el waitpid, el padre espera a que el hijo termine, y asi sucesivamente
    for (int i = 0; i < num_procesos; i++){

        // 2. creo el proceso hijo
        if ((PID = fork()) < 0){
            perror("Error en el fork\n");
            exit(EXIT_FAILURE);
        }

        // en el proceso padre si PID no es nulo , caso hijo
        // PID = 1, proceso init, se ha convertido en padre 
        // PID del padre es 1 cuando el proceso hijo se convierte en padre de nuevos procesos
        // cuando es 1, padre ha terminado antes de que los procesos hijos puedan imprimir su mensaje
        if (PID){
            //waitpid(PID, NULL, 0); // si añado un wait1 todos esperan y el padre no puede terminar antes que los hijos
            printf("hijo: %d,  padre: %d,  \n", getpid(), getppid());
            break;
        }
    }
    */
    

    
    // 3. creo la jerarquia de procesos 2
    // esta jerarquia el proceso padre crea muchos hijos
     for (int i=1; i < num_procesos; i++){
         if ( (PID= fork()) == -1){
             fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
             exit(-1);
         }

         // caso en el que no sea 1 es el proceso padre ?¿ el proceso padre es 1 no 0
         if (!PID){
             printf("hijo: %d,  padre: %d,  \n", getpid(), getppid());
             break;
         }
     }
     

    // mi caso de jerarquia de procesos, que sea secuencial
    // De este modo, mostramos los procesos en orden de creación, de más nuevo a más antiguo. Nótese que el PID del hijo es el PID del padre +1, excepto del proceso padre de todos
    // hago lo mismo añadiendo un waitpid en la jerarquia 1
    /*
    pid_t id_proceso;   
    pid_t id_padre;
    pid_t pid = 0;
    int i = 0;
    while (++i < 20 && pid == 0)
    {
        // creamos el hijillo
        if ((pid = fork()) < 0)
        {
            perror("\nNo se ha podido crear el hijo\n");
            exit(-1);
        }
    }
    id_proceso = getpid();
    id_padre = getppid();
    while (wait(NULL) != -1)
        ;
    printf("PID = %d, PPID = %d\n",
           id_proceso, id_padre);
    exit(0);
    */
}