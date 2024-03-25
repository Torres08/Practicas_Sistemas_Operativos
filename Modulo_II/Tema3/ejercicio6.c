
/*
    Nombre: Ejercicio6.c
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    Ejercicio 6: ¿Qué hace el siguiente programa?

    Ejecucion del programa: $> ./ejercicio6
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // 1. creo pid y estado porque voy a manejar fork y wait
    pid_t pid;
    int estado;

    // 2. creo proceso hijo
    if ((pid = fork()) < 0)
    {
        perror("\nError en el fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        // 3. caso hijo
        // proceso hijo ejecutando el programa, hago lld con ejercicio5
        // usamos execl para ejecutar la funcion , indicamos ruta del programa, orden y el nombre de nuestro programa
        // ldd imprime las bibliotecas de las que depende el programa
        if ((execl("/usr/bin/ldd", "ldd", "./papelera/ejercicio5") < 0))
        {
            perror("\nError en el execl");
            exit(EXIT_FAILURE);
        }
    }

    // 4. caso padre, espera al hijo
    wait(&estado);

    /*
    <estado> mantiene información codificada a nivel de bit sobre el motivo de finalización del proceso hijo
    que puede ser el número de señal o 0 si alcanzó su finalización normalmente.
    Mediante la variable estado de wait(), el proceso padre recupera el valor especificado por el proceso hijo como argumento de la llamada exit(), pero desplazado 1 byte porque el sistema incluye en el byte menos significativo
    el código de la señal que puede estar asociada a la terminación del hijo. Por eso se utiliza estado>>8
    de forma que obtenemos el valor del argumento del exit() del hijo.
    */

    // 5. imprimo el estado del hijo, estado >> 8 para que no me imprima la señal
    // finaliza con 0: ejecucion exito
    printf("\nMi hijo %d ha finalizado con el estado %d\n", pid, estado >> 8);

    exit(EXIT_SUCCESS);
}