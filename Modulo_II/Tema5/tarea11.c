/*

    Nombre: tarea11.c
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    Tarea 11: ejemplo uso signempryset, sigaddset sigsuspend
    en el siguiente ejemplo se suspende la ejecucion del proceso actual hasta que 
    reciba una señal distinta de 
    SIGUSR1
    
    Ejecucion del programa: $> ./Tarea11

    en una terminal
    ./papelera/tarea11
    Killed


    en otra
    ps aux | grep tarea 11 -> obtengo el PID
    kill -s SIGUSR1 PID -> mato el programa anterior

*/

#include <stdio.h>
#include <signal.h>

int main() {
    sigset_t new_mask;
    
    // vaciamos la máscara
    sigemptyset(&new_mask);
    
    // rellenamos la máscara con todas las señales
    sigfillset(&new_mask);
    
    // eliminamos SIGUSR1
    sigaddset(&new_mask, SIGUSR1);
    
    // cuando suspendamos el programa no reaccionará a ninguna señal excepto SIGUSR1
    sigsuspend(&new_mask);

    // SE REANUDA CUANDO LE ENVIO UN KILL -S sigusr1 PID
}