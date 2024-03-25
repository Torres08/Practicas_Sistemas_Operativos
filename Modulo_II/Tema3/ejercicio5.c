/*
    Nombre: Ejercicio5.c
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    Ejercicio 5: modificacion ejercicio 4, espera el padre primero a los impares 1,3,5 y luego a los pares 2,4

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
    int contador = 5;

    // 6. espero a los impares, en cualquier orden de llegada 
    for(int i = 1; i <= 5; i+=2){
        pid_hijo = waitpid(-1, &estado, 0); // -1 espero a cualquier hijo
        
        contador--;
        // para el resto de pid que queda va a ser NUM HIJOS - (i + 1), + 1 por que no puede ser 5
        printf("Acaba de finalizar mi hijo impar con PID: %d, solo me quedan %d vivos\n", pid_hijo, contador);
    }

    for(int i = 2; i <= 5; i+=2){
        pid_hijo = waitpid(-1, &estado, 0); // -1 espero a cualquier hijo
        contador--;
        // para el resto de pid que queda va a ser NUM HIJOS - (i + 1), + 1 por que no puede ser 5
        printf("Acaba de finalizar mi hijo par con PID: %d, solo me quedan %d vivos\n", pid_hijo, contador);
    }
    

    exit(EXIT_SUCCESS);
}