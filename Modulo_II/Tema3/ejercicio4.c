/*
    Nombre: Ejercicio4.c
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    Ejercicio 4: Implementa un programa que lance 5 procesos hijos. Cada uno de ellos se identificara en la salida estandar
    mostrando el mensaje <Soy el hijo PID>. El proceso padre simplemente tendrá que esperar a que todos sus hijos terminen.
    Cada vez que un hijo termina, el proceso padre mostrará el mensaje <Acaba de finalizar mi hijo con PID> <solo me quedan NUM_HIJOS vivos>

    Ejecucion del programa: $> ./ejercicio4
*/

#include <sys/types.h>
#include <sys/wait.h> // waitpid
#include <unistd.h>   // fork
#include <stdio.h>    // perror
#include <stdlib.h>

int main()
{
    // 1. variables que necesito, PID, int estado
    pid_t PID;

    // 2. creo 5 procesos hijos
    for (int i = 0; i < 5; i++)
    {
        // 3. creo proceso hijo
        if ((PID = fork()) < 0)
        {
            perror("Error en el fork\n");
            exit(EXIT_FAILURE);
        }

        // 4. sigo la jerarquia 2, creo un padre con varios hijos

        if (PID == 0)
        {
            printf("Soy el hijo con PID: %d, el hijo de PPID = %d\n", getpid(), getppid());
            exit(EXIT_SUCCESS);
        }

    
    }

    // 5. caso padre, espero a que terminen los hijos
    // caso padre -> else, no tiene sentido hacerlo dentro del bucle 
    int estado;
    pid_t pid_hijo;

    for(int i = 0; i < 5; i++){
        pid_hijo = wait(&estado);

        // para el resto de pid que queda va a ser NUM HIJOS - (i + 1), + 1 por que no puede ser 5
        printf("Acaba de finalizar mi hijo con PID: %d, solo me quedan %d vivos\n", pid_hijo, 5 - i - 1);
    }
    

    exit(EXIT_SUCCESS);
}